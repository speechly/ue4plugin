#include "Speechgrinder.h"

DEFINE_LOG_CATEGORY(LogSG);

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

void USpeechgrinder::Connect(const FString& AppId, const FString& LanguageCode)
{
	Recorder.Stop();
    if (ClientThread)
    {
        ClientThread->Kill(true);
        ClientThread = nullptr;
    }
	FString DeviceId = FGenericPlatformMisc::GetDeviceId();
	Client.Reset(new SpeechgrinderClient("api.speechly.com", std::string(TCHAR_TO_UTF8(*DeviceId)), std::string(TCHAR_TO_UTF8(*AppId)), std::string(TCHAR_TO_UTF8(*LanguageCode)), sg::kSampleRate));
    ClientThread = FRunnableThread::Create(Client.Get(), TEXT("SpeechgrinderClient"), 0);
}

bool USpeechgrinder::Start()
{
    if (IsConnected())
    {
		bIsBuffering = true;
		AudioBuffer.Empty();
		Recorder.Start();

        SluRequest Request;
        Request.mutable_event()->set_event(SluEvent_Event_START);
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

bool USpeechgrinder::Stop()
{
    Recorder.Stop();
    if (IsConnected())
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
	OutError = false;
	if (!IsConnected())
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
			DrainBuffer();
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
			if (OutSpeechgrinderResponse.Utterance.bIsFinal)
			{
				OutSpeechgrinderResponse.Utterance.Alternatives.Sort([](const auto& A, const auto& B) { return A.Confidence < B.Confidence; });
			}
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

UFUNCTION(BlueprintCallable)
void USpeechgrinder::ReadLatestResults(TArray<FSpeechgrinderResponse>& OutSpeechgrinderResponses, bool& OutError)
{
	OutSpeechgrinderResponses.Empty();
	OutError = false;
	if (!IsConnected())
	{
		OutError = true;
		return;
	}

	TMap<FString, FSpeechgrinderResponse> IdToResponse;
	while (true)
	{
		FSpeechgrinderResponse Response;
		bool bError;
		bool bGotResult = Read(Response, bError);
		if (!bGotResult)
		{
			break;
		}
		if (bError)
		{
  			OutError = true;
			return;
		}

		if (Response.Event == ESpeechgrinderResponseType::Utterance)
		{
			IdToResponse.Add(Response.UtteranceId, Response);
		}
		else
		{
			for (const auto& pair : IdToResponse)
			{
				OutSpeechgrinderResponses.Add(pair.Value);
			}
			IdToResponse.Empty();
			OutSpeechgrinderResponses.Add(Response);
		}
	}
	for (const auto& pair : IdToResponse)
	{
		OutSpeechgrinderResponses.Add(pair.Value);
	}
}

bool USpeechgrinder::IsConnected() const
{
	return Client.IsValid() && !Client->HasError();
}

void USpeechgrinder::OnSpeechAudio(const float* Audio, const int32 AudioLength)
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
		SluRequest Request;
		Request.set_audio(CharAudio.GetData(), OutputAudioLength);
		Client->Write(Request);
	}
}

void USpeechgrinder::DrainBuffer()
{
	if (!bIsBuffering)
	{
		return;
	}
	bIsBuffering = false;

	SluRequest Request;
	Request.set_audio(AudioBuffer.GetData(), AudioBuffer.Num());
	Client->Write(Request);
	AudioBuffer.Empty();
}
