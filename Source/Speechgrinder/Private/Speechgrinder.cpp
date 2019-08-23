#include "Speechgrinder.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

#include <limits>

DEFINE_LOG_CATEGORY(LogSG);

namespace {
	static const int kSampleRate = 16000;
	static const int kNumFramesDesired = 1024;
};


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

bool USpeechgrinder::isConnected() const
{
	return Client.IsValid() && !Client->HasError();
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
