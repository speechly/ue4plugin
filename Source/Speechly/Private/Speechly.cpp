#include "Speechly.h"

DEFINE_LOG_CATEGORY(LogSG);

USpeechly::USpeechly() : ClientThread{}
{
    verifyf(FPlatformProcess::SupportsMultithreading(), TEXT("Speechly requires multithreading"));
	Recorder.Callback = this;
}

USpeechly::~USpeechly()
{
	Recorder.Stop();
	if (ClientThread)
    {
        ClientThread->Kill(true);
        ClientThread = nullptr;
    }
}

void USpeechly::Connect(const FString& AppId, const FString& LanguageCode)
{
	Recorder.Stop();
    if (ClientThread)
    {
        ClientThread->Kill(true);
        ClientThread = nullptr;
    }
	FString DeviceId = FGenericPlatformMisc::GetDeviceId();
	Client.Reset(new SpeechlyClient("api.speechly.com", std::string(TCHAR_TO_UTF8(*DeviceId)), std::string(TCHAR_TO_UTF8(*AppId)), std::string(TCHAR_TO_UTF8(*LanguageCode)), sg::kSampleRate));
    ClientThread = FRunnableThread::Create(Client.Get(), TEXT("SpeechlyClient"), 0);
}

bool USpeechly::Start()
{
    if (IsConnected())
    {
		bIsBuffering = true;
		AudioBuffer.Empty();
		Recorder.Start();

        SLURequest Request;
        Request.mutable_event()->set_event(SLUEvent_Event_START);
        bool bSuccess = Client->Write(Request);
        if (!bSuccess)
        {
            Client.Reset();
			Recorder.Stop();
        }
        
        return bSuccess;
    }
    return false;
}

bool USpeechly::Stop()
{
    Recorder.Stop();
    if (IsConnected())
    {
        SLURequest Request;
        Request.mutable_event()->set_event(SLUEvent_Event_STOP);
        bool bSuccess = Client->Write(Request);
        if (!bSuccess)
        {
            Client.Reset();
        }
        return bSuccess;
    }
    return false;
}

bool USpeechly::Read(FSpeechlyResponse& OutSpeechlyResponse, bool& OutError)
{
	OutError = false;
	if (!IsConnected())
	{
		OutError = true;
		return false;
	}

	OutSpeechlyResponse.bHasError = false;
    SLUResponse Response;
    bool bSuccess = Client->Read(Response);
	if (bSuccess)
	{
		if (Response.has_started())
		{
			OutSpeechlyResponse.Event = ESpeechlyResponseType::Started;
			OutSpeechlyResponse.AudioContext = Response.started().audio_context().c_str();
			DrainBuffer();
		}
		else if (Response.has_transcript())
		{
			OutSpeechlyResponse.Event = ESpeechlyResponseType::Transcript;
			auto Transcript = Response.transcript();
			OutSpeechlyResponse.AudioContext = Transcript.audio_context().c_str();
			OutSpeechlyResponse.Transcript.SegmentId = Transcript.segment_id();
			OutSpeechlyResponse.Transcript.Word = Transcript.word().c_str();
			OutSpeechlyResponse.Transcript.Index = Transcript.index();
			OutSpeechlyResponse.Transcript.StartTime = Transcript.start_time();
			OutSpeechlyResponse.Transcript.EndTime = Transcript.end_time();
		}
		else if (Response.has_entity())
		{
			auto Entity = Response.entity();
			OutSpeechlyResponse.Event = ESpeechlyResponseType::Entity;
			OutSpeechlyResponse.AudioContext = Entity.audio_context().c_str();
			OutSpeechlyResponse.Entity.SegmentId = Entity.segment_id();
			OutSpeechlyResponse.Entity.Entity = Entity.entity().c_str();
			OutSpeechlyResponse.Entity.Value = Entity.value().c_str();
			OutSpeechlyResponse.Entity.StartPosition = Entity.start_position();
			OutSpeechlyResponse.Entity.EndPosition = Entity.end_position();
		}
		else if (Response.has_intent())
		{
			auto Intent = Response.intent();
			OutSpeechlyResponse.Event = ESpeechlyResponseType::Intent;
			OutSpeechlyResponse.AudioContext = Intent.audio_context().c_str();
			OutSpeechlyResponse.Intent.SegmentId = Intent.segment_id();
			OutSpeechlyResponse.Intent.Intent = Intent.intent().c_str();
		}
		else if (Response.has_segment_end())
		{
			auto SegmentEnd = Response.segment_end();
			OutSpeechlyResponse.Event = ESpeechlyResponseType::SegmentEnd;
			OutSpeechlyResponse.AudioContext = SegmentEnd.audio_context().c_str();
			OutSpeechlyResponse.SegmentEnd.SegmentId = SegmentEnd.segment_id();
		}
		else if (Response.has_finished())
		{
			OutSpeechlyResponse.Event = ESpeechlyResponseType::Finished;
			auto finished = Response.finished();
			OutSpeechlyResponse.AudioContext = finished.audio_context().c_str();
			OutSpeechlyResponse.bHasError = finished.has_error();
			if (finished.has_error())
			{
				OutSpeechlyResponse.ErrorCode = finished.error().code().c_str();
				OutSpeechlyResponse.ErrorMessage = finished.error().message().c_str();
			}

			// Stop recording if currently active UtteranceId was finished
			if (OutSpeechlyResponse.AudioContext == LastAudioContext)
			{
				Recorder.Stop();
			}
		}
        else
        {
			OutSpeechlyResponse.Event = ESpeechlyResponseType::Unknown;
        }
    }
    return bSuccess;
}

bool USpeechly::IsConnected() const
{
	return Client.IsValid() && !Client->HasError();
}

void USpeechly::OnSpeechAudio(const float* Audio, const int32 AudioLength)
{
 	if (!IsConnected())
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
	uint16* ShortAudio = reinterpret_cast<uint16*>(CharAudio.GetData());
	for (int32 i = 0; i < AudioLength; ++i)
	{
		int32 ScaledSample = static_cast<int32>(Audio[i] * (Audio[i] < 0.f ? 32768.f : 32767.f));
		ScaledSample = FPlatformMath::Max(-32768, FPlatformMath::Min(32767, ScaledSample));
		int16 Sample = static_cast<int16>(ScaledSample);
		ShortAudio[i] = Sample;
	}

	if (bIsBuffering)
	{
		AudioBuffer.Append(CharAudio.GetData(), OutputAudioLength);
	}
	else
	{
		SLURequest Request;
		Request.set_audio(CharAudio.GetData(), OutputAudioLength);
		Client->Write(Request);
	}
}

void USpeechly::DrainBuffer()
{
	if (!bIsBuffering)
	{
		return;
	}
	bIsBuffering = false;

	SLURequest Request;
	Request.set_audio(AudioBuffer.GetData(), AudioBuffer.Num());
	Client->Write(Request);
	AudioBuffer.Empty();
}
