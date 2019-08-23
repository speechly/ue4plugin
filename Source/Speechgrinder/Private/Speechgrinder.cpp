#include "Speechgrinder.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

#include <limits>

DEFINE_LOG_CATEGORY(LogSG);

namespace {
	static const int kSampleRate = 16000;
	static const int kNumFramesDesired = 1024;
};

SpeechgrinderClient::SpeechgrinderClient(const std::string& Address, const std::string& DeviceId, const std::string& AppId, const std::string& LanguageCode) : Address{Address}, DeviceId{DeviceId}, AppId{AppId}, LanguageCode{LanguageCode}
{
    FString Pem;
    FString PemPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()).Append(TEXT("NonUFS/roots.pem"));
    if (FFileHelper::LoadFileToString(Pem, *PemPath, {}))
    {
        Credentials = grpc::SslCredentials(grpc::SslCredentialsOptions{std::string(TCHAR_TO_UTF8(*Pem))});
    }
    else
    {
        UE_LOG(LogSG, Error, TEXT("Could not read '%s' for root certificates, using system certificates which probably won't work."), *PemPath);
        Credentials = grpc::SslCredentials(grpc::SslCredentialsOptions{});
    }
}

bool SpeechgrinderClient::Write(const SluRequest& Request)
{
    if (bHasError || !bIsRunning)
    {
        UE_LOG(LogSG, Error, TEXT("Tried to write to SpeechgrinderClient that is not running"));
        return false;
    }
    return RequestQueue.Enqueue(Request);
}

bool SpeechgrinderClient::Read(SluResponse& OutResponse)
{
    if (bHasError || !bIsRunning)
    {
        UE_LOG(LogSG, Error, TEXT("Tried to read from SpeechgrinderClient that is not running"));
        return false;
    }
    return ResponseQueue.Dequeue(OutResponse);
}

bool SpeechgrinderClient::Init()
{
    Channel = grpc::CreateChannel(Address, Credentials);
    
    auto IdentityStub = Identity::NewStub(Channel);
    
    grpc::ClientContext IdentityContext;
    
    LoginRequest Request;
    Request.set_device_id(DeviceId);
    Request.set_app_id(AppId);
    LoginResponse LoginResponse;
    
    grpc::Status Status = IdentityStub->Login(&IdentityContext, Request, &LoginResponse);
    if (!Status.ok())
    {
        Channel.reset();
        return false;
    }
    Context.AddMetadata("authorization", "Bearer " + LoginResponse.token());
    return true;
}

uint32 SpeechgrinderClient::Run()
{
    SluStub = Slu::NewStub(Channel);

    uintptr_t StreamSeq = ++Seq;
    Stream = SluStub->AsyncStream(&Context, &CompletionQueue, reinterpret_cast<void*>(StreamSeq));
    
    // Wait for Stream to open
    {
        void* Tag;
        bool Ok;
        if (CompletionQueue.Next(&Tag, &Ok))
        {
            if (!Ok || Tag != reinterpret_cast<void*>(StreamSeq))
            {
                UE_LOG(LogSG, Error, TEXT("Unexpected Stream open"));
                bHasError = true;
                return 1;
            }
        }
        else
        {
            UE_LOG(LogSG, Error, TEXT("Stream prematurely shut down"));
            bHasError = true;
            return 1;
        }
    }

    // Configure stream
    {
        SluRequest Request;
        SluConfig* Config = Request.mutable_config();
        Config->set_channels(1);
        Config->set_sample_rate_hertz(kSampleRate);
        Config->set_language_code(LanguageCode);
        
		StreamWrite(Request);
        void* Tag;
        bool Ok;
        if (CompletionQueue.Next(&Tag, &Ok))
        {
			HandleTag(Tag);
            if (!Ok || Tag != reinterpret_cast<void*>(LastWriteSeq))
            {
				SetError("Could not configure stream");
                return 1;
            }
        }
        else
        {
			SetError("Stream error");
            return 1;
        }
	}

    while (bIsRunning && !bHasError)
    {
        if (CanWrite())
        {
            SluRequest Request;
            if (RequestQueue.Dequeue(Request))
            {
				StreamWrite(Request);
            }
        }
        if (CanRead())
        {
			StreamRead(&Response);
        }
        
        void* Tag;
        bool Ok;
        gpr_timespec Deadline = gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC), gpr_time_from_millis(2, GPR_TIMESPAN));
        grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
        if (NextStatus == grpc::CompletionQueue::GOT_EVENT)
        {
			HandleTag(Tag);
            if (Tag == reinterpret_cast<void*>(LastWriteSeq))
            {
                if (!Ok)
                {
					SetError("Speechgrinder Write failed");
					return 1;
                }
            }
            else if (Tag == reinterpret_cast<void*>(LastReadSeq))
            {
                if (!Ok)
                {
					SetError("Speechgrinder Read failed");
					return 1;
                }
                else
                {
                    ResponseQueue.Enqueue(Response);
                }
            }
            else
            {
                UE_LOG(LogSG, Warning, TEXT("Speechgrinder unknown tag"));
                if (!Ok)
                {
					SetError("Unknown tag with an error");
					return 1;
                }
            }
        }
        else if (NextStatus == grpc::CompletionQueue::TIMEOUT)
        {
            // Noop
        }
        else if (NextStatus == grpc::CompletionQueue::SHUTDOWN)
        {
            bIsRunning = false;
            break;
        }
    }

    return 0;
}

void SpeechgrinderClient::Exit()
{
    if (Stream)
    {
        gpr_timespec Deadline = gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC), gpr_time_from_seconds(5, GPR_TIMESPAN));

		// GRPC shutdown from client side is a complicated system,
		// the following code is based on this understanding:
		// - Context cancellation races with reads, so read until it fails
		// - Stream can only be finished if there are no reads and writes pending
		// - Stream finishes requires server status (eg. cancel or close)
		// - CompletionQueue must be shutdown
		// - CQ can only be shutdown after the queue is drained
		// - CQ shutdown cannot be started if we are enqueueing requests

		// Activate cancellation as we don't want to wait for server to close the connection
		Context.TryCancel();

		// Drain requests and launch reads until stopped from cancellation
		while (true)
        {
			if (CanRead())
			{
				SluResponse Response;
				StreamRead(&Response);
			}

            void* Tag;
            bool Ok;
            grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
            if (NextStatus == grpc::CompletionQueue::GOT_EVENT)
            {
				HandleTag(Tag);
				if (!Ok)
				{
					break;
				}
            }
			else
			{
				UE_LOG(LogSG, Warning, TEXT("Timed out or shutdown while waiting for cancellation"));
				break;
			}
        }

		// Finish the stream
		grpc::Status Status;
		uintptr_t FinishDoneSeq;
        Stream->Finish(&Status, reinterpret_cast<void*>(FinishDoneSeq = ++Seq));
		while (true)
		{
			void* Tag;
			bool Ok;
			grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
			if (NextStatus == grpc::CompletionQueue::GOT_EVENT)
			{
				if (Tag == reinterpret_cast<void*>(FinishDoneSeq) || !Ok)
				{
					break;
				}
				UE_LOG(LogSG, Warning, TEXT("Received unknown tag when waiting for finish"));
			}
			else if (NextStatus == grpc::CompletionQueue::TIMEOUT)
			{
				UE_LOG(LogSG, Warning, TEXT("Speechgrinder finish timed out, this can result in a memory leak"));
				break;
			}
			else if (NextStatus == grpc::CompletionQueue::SHUTDOWN)
			{
				break;
			}
		}

        CompletionQueue.Shutdown();
        while (true)
        {
            void* Tag;
            bool Ok;
            grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
            if (NextStatus == grpc::CompletionQueue::TIMEOUT)
            {
                UE_LOG(LogSG, Warning, TEXT("Speechgrinder shutdown timed out, this can result in a memory leak"));
				return;
            }
            else if (NextStatus == grpc::CompletionQueue::SHUTDOWN)
            {
                // Drained and shutdown
                return;
            }
        }
    }
}

void SpeechgrinderClient::Stop()
{
    bIsRunning = false;
}

bool SpeechgrinderClient::CanWrite()
{
	return bWriteAllowed;
}

bool SpeechgrinderClient::CanRead()
{
	return bReadAllowed;
}

void SpeechgrinderClient::StreamWrite(const SluRequest& Request)
{
	check(Stream);
	check(CanWrite());
	Stream->Write(Request, reinterpret_cast<void*>(LastWriteSeq = ++Seq));
	bWriteAllowed = false;
}

void SpeechgrinderClient::StreamRead(SluResponse* OutResponse)
{
	check(Stream);
	check(CanRead());
	Stream->Read(OutResponse, reinterpret_cast<void*>(LastReadSeq = ++Seq));
	bReadAllowed = false;
}

void SpeechgrinderClient::HandleTag(void* Tag)
{
	if (Tag == reinterpret_cast<void*>(LastWriteSeq))
	{
		bWriteAllowed = true;
	}
	else if (Tag == reinterpret_cast<void*>(LastReadSeq))
	{
		bReadAllowed = true;
	}
}

void SpeechgrinderClient::SetError(const FString& Message)
{
	UE_LOG(LogSG, Error, TEXT("%s"), *Message);
	bHasError = true;
	bIsRunning = false;
}

FSpeechRecorder::FSpeechRecorder()
{
}

FSpeechRecorder::~FSpeechRecorder()
{
    AudioCapture.AbortStream();
    AudioCapture.CloseStream();
}

void FSpeechRecorder::Start()
{
	FScopeLock Lock(&CriticalSection);
	if (!AudioCapture.IsStreamOpen())
    {
        AudioCapture.GetDefaultCaptureDeviceInfo(OutInfo);
		generateFilter();
        FAudioCaptureStreamParam StreamParam;
        StreamParam.Callback = this;
        StreamParam.NumFramesDesired = kNumFramesDesired;
        verifyf(AudioCapture.OpenDefaultCaptureStream(StreamParam), TEXT("Could not open capture stream"));
        AudioCapture.StartStream();
    }
    verifyf(AudioCapture.IsStreamOpen(), TEXT("Stream was not opened"));
    verifyf(AudioCapture.IsCapturing(), TEXT("Stream is not capturing"));
    bIsCapturing = true;
}

void FSpeechRecorder::Stop()
{
    FScopeLock Lock(&CriticalSection);
    bIsCapturing = false;
	Buffer.Empty();
}

void FSpeechRecorder::OnAudioCapture(float* AudioData, int32 NumFrames, int32 NumChannels, double StreamTime, bool bOverflow)
{
	FScopeLock Lock(&CriticalSection);
	if (!bIsCapturing)
	{
		return;
	}

	// Pick the first channel
	for (int32 i = 0; i < NumFrames; ++i)
	{
		Buffer.Add(AudioData[i * NumChannels]);
	}

	int32 OutputLength = ceilf((Buffer.Num() - Filter.Num()) / SampleRatio);
	Output.Empty(kNumFramesDesired);

	for (int32 i = 0; i < OutputLength; ++i)
	{
		Output.Add(0.0f);
		int32 Offset = roundf(SampleRatio * i);
		for (int32 j = 0; j < Filter.Num(); ++j)
		{
			Output[i] += Buffer[Offset + j] * Filter[j];
		}
	}

	int32 RemainingOffset = roundf(SampleRatio * OutputLength);
	if (RemainingOffset < NumFrames)
	{
		Buffer.Empty(NumFrames);
		for (int32 i = RemainingOffset; i < NumFrames; ++i)
		{
			float Frame = 0.0f;
			for (int32 channel = 0; channel < NumChannels; ++channel)
			{
				Frame += AudioData[i * (channel + 1)];
			}
			Buffer.Add(Frame / NumChannels);
		}
	}
	else
	{
		Buffer.Empty(kNumFramesDesired);
	}

	verifyf(Callback, TEXT("Audio callback not defined"));
	Callback->OnSpeechAudio(Output.GetData(), OutputLength);
}

void FSpeechRecorder::generateFilter()
{
	int32 SampleRate = OutInfo.PreferredSampleRate;
	int32 Cutoff = kSampleRate;
	SampleRatio = static_cast<float>(SampleRate) / Cutoff;
	int32 FilterLength = 23;
	Filter.Empty(FilterLength);
	auto Sinc = [](float x) {
		if (x == 0.0f)
		{
			return 1.0f;
		}
		float PIx = PI * x;
		return sin(PIx) / PIx;
	};
	float Sum = 0;
	for (int32 i = 0; i < FilterLength; ++i)
	{
		float x = Sinc(Cutoff * 2.0f / SampleRate * (i - (FilterLength - 1) / 2.0f));
		Filter.Add(x);
		Sum += x;
	}
	for (int32 i = 0; i < Filter.Num(); ++i)
	{
		Filter[i] /= Sum;
	}
}

USpeechgrinder::USpeechgrinder() : ClientThread{}
{
    verifyf(FPlatformProcess::SupportsMultithreading(), TEXT("Speechgrinder requires multithreading"));
	Recorder.Callback = this;
}

USpeechgrinder::~USpeechgrinder()
{
	Recorder.Stop();
	if (ClientThread)
    {
        ClientThread->Kill(true);
        ClientThread = nullptr;
    }
}

void USpeechgrinder::Connect(const FString& DeviceId, const FString& AppId, const FString& LanguageCode)
{
	Recorder.Stop();
    if (ClientThread)
    {
        ClientThread->Kill(true);
        ClientThread = nullptr;
    }
	Client.Reset(new SpeechgrinderClient("api.speechgrinder.com", std::string(TCHAR_TO_UTF8(*DeviceId)), std::string(TCHAR_TO_UTF8(*AppId)), std::string(TCHAR_TO_UTF8(*LanguageCode))));
    ClientThread = FRunnableThread::Create(Client.Get(), TEXT("SpeechgrinderClient"), 0);
}

bool USpeechgrinder::Start()
{
    if (isConnected())
    {
        SluRequest Request;
        Request.mutable_event()->set_event(SluEvent_Event_START);
        bool bSuccess = Client->Write(Request);
        if (!bSuccess)
        {
            Client.Reset();
        }
        
        return bSuccess;
    }
    return false;
}

bool USpeechgrinder::Stop()
{
    Recorder.Stop();
    if (isConnected())
    {
        SluRequest Request;
        Request.mutable_event()->set_event(SluEvent_Event_STOP);
        bool bSuccess = Client->Write(Request);
        if (!bSuccess)
        {
            Client.Reset();
        }
        return bSuccess;
    }
    return false;
}

bool USpeechgrinder::Read(FSpeechgrinderResponse& OutSpeechgrinderResponse, bool& OutError)
{
	if (!isConnected())
	{
		OutError = true;
		return false;
	}

	OutSpeechgrinderResponse.bHasError = false;
    SluResponse Response;
    bool bSuccess = Client->Read(Response);
    if (bSuccess)
    {
        if (Response.has_started())
        {
			OutSpeechgrinderResponse.Event = ESpeechgrinderResponseType::Started;
			OutSpeechgrinderResponse.UtteranceId = Response.started().utterance_id().c_str();
            Recorder.Start();
        }
        else if (Response.has_utterance())
        {
			OutSpeechgrinderResponse.Event = ESpeechgrinderResponseType::Utterance;
			auto Utterance = Response.utterance();
			OutSpeechgrinderResponse.UtteranceId = Utterance.utterance_id().c_str();
			OutSpeechgrinderResponse.Utterance.bIsFinal = Utterance.type() == "finalItem";
			for (auto Alt : Utterance.alternatives())
			{
				FSpeechgrinderAlternative Alternative;
				Alternative.Confidence = Alt.confidence();
				for (auto Tok : Alt.tokens())
				{
					FSpeechgrinderToken Token;
					Token.Text = Tok.text().c_str();
					Token.TextWithTrailingSpace = Tok.text().c_str();
					Token.Lemma = Tok.lemma().c_str();
					Token.Pos = Tok.pos().c_str();
					Token.Tag = Tok.tag().c_str();
					Token.Case = Tok.case_().c_str();
					Token.Number = Tok.number().c_str();
					Token.EntityType = Tok.entity_type().c_str();
					Token.PositionInEntity = Tok.position_in_entity();
					Token.bIsSegmentStart = Tok.is_segment_start();
					Token.TrailingSilence = Tok.trailing_silence();
					Alternative.Tokens.Add(Token);
				}
				OutSpeechgrinderResponse.Utterance.Alternatives.Add(Alternative);
			}
			OutSpeechgrinderResponse.Utterance.Alternatives.Sort([](const auto & A, const auto & B) { return A.Confidence < B.Confidence; });
		}
		else if (Response.has_finished())
		{
			OutSpeechgrinderResponse.Event = ESpeechgrinderResponseType::Finished;
			auto finished = Response.finished();
			OutSpeechgrinderResponse.UtteranceId = finished.utterance_id().c_str();
			OutSpeechgrinderResponse.bHasError = finished.has_error();
			if (finished.has_error())
			{
				OutSpeechgrinderResponse.ErrorCode = finished.error().code().c_str();
				OutSpeechgrinderResponse.ErrorMessage = finished.error().message().c_str();
			}

			// Stop recording if currently active UtteranceId was finished
			if (OutSpeechgrinderResponse.UtteranceId == LastUtteranceId)
			{
				Recorder.Stop();
			}
		}
        else
        {
			OutSpeechgrinderResponse.Event = ESpeechgrinderResponseType::Unknown;
        }
    }
    return bSuccess;
}

void USpeechgrinder::OnSpeechAudio(const float* Audio, const int32 AudioLength)
{
	if (!isConnected())
	{
		Recorder.Stop();
		return;
	}
	if (AudioLength == 0)
	{
		return;
	}
	int32 OutputAudioLength = AudioLength * 2; // 16-bit samples in 8-bit char
	if (CharAudio.Num() < OutputAudioLength)
	{
		CharAudio.SetNumUninitialized(OutputAudioLength);
	}
	for (int32 i = 0; i < AudioLength; ++i)
	{
		int16 Sample = static_cast<int16>(Audio[i] * (1 << 15));
		// First convert to 8-bit halves in an unsigned format to get raw bytes
		unsigned char A = static_cast<unsigned char>(Sample & 0xff);
		unsigned char B = static_cast<unsigned char>((Sample >> 8) & 0xff);
		// Then convert to platform signedness
		CharAudio[i * 2] = static_cast<char>(A);
		CharAudio[i * 2 + 1] = static_cast<char>(B);
	}
	SluRequest Request;
	Request.set_audio(CharAudio.GetData(), OutputAudioLength);
	Client->Write(Request);
}
