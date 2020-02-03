#include "Speechly.h"

#include "Containers/Ticker.h"

DEFINE_LOG_CATEGORY(LogSG);

USpeechly::USpeechly() : ClientThread{}
{
	verifyf(FPlatformProcess::SupportsMultithreading(), TEXT("Speechly requires multithreading"));
	Recorder.Callback = this;
}

USpeechly::~USpeechly()
{
	FTicker::GetCoreTicker().RemoveTicker(TickerHandle);
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

	SilenceCount = 0;
	Responses.Empty();
	ContextToKeys.Empty();

	FString DeviceId = FGenericPlatformMisc::GetDeviceId();
	Client.Reset(new SpeechlyClient("api.speechly.com", std::string(TCHAR_TO_UTF8(*DeviceId)), std::string(TCHAR_TO_UTF8(*AppId)), std::string(TCHAR_TO_UTF8(*LanguageCode)), sg::kSampleRate));
	ClientThread = FRunnableThread::Create(Client.Get(), TEXT("SpeechlyClient"), 0);
	FTicker::GetCoreTicker().RemoveTicker(TickerHandle);
	TickerHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this](float TimeDelta) { return Tick(TimeDelta); }));
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

bool USpeechly::IsConnected() const
{
	return Client.IsValid() && !Client->HasError();
}

bool USpeechly::Tick(float DeltaTime)
{
	if (!IsConnected())
	{
		OnSpeechlyError.Broadcast("", "Disconnected");
		return false;
	}

	// TODO: Read x amount of queue, not just one per tick
	TSet<FString> ChangedKeys;
	TSet<FString> FinishedContexts;
	TMap<FString, FString> Errors;

	int MaxReads = 10;
	while (MaxReads--)
	{
		SLUResponse Response;
		bool bSuccess = Client->Read(Response);
		if (!bSuccess)
		{
			break;
		}
		if (Response.has_started())
		{
			bIsBuffering = false;
			LastAudioContext = Response.started().audio_context().c_str();
		}
		else if (Response.has_finished())
		{
			auto finished = Response.finished();
			FString Context = finished.audio_context().c_str();
			if (finished.has_error())
			{
				Errors.Emplace(Context, finished.error().message().c_str());
			}

			// Stop recording if currently active UtteranceId was finished
			if (Context == LastAudioContext)
			{
				Recorder.Stop();
			}

			// Set to resend all responses with non final result sent previously
			TSet<FString>* Contexts = ContextToKeys.Find(Context);
			if (Contexts != nullptr)
			{
				for (const FString& Key : *Contexts)
				{
					FSpeechlyResponse* Out = Responses.Find(Key);
					if (Out != nullptr && !Out->bIsFinal)
					{
						ChangedKeys.Add(Key);
						Out->bIsFinal = true;
					}
				}
			}

			FinishedContexts.Add(Context);
		}
		else if (Response.has_transcript())
		{
			FString Key = KeyOfMessage(Response.transcript());
			ChangedKeys.Add(Key);
			FSpeechlyResponse& Out = Responses.FindOrAdd(Key);
			if (!Out.Transcript.IsEmpty())
			{
				Out.Transcript.Append(TEXT(" "));
			}
			Out.Transcript.Append(Response.transcript().word().c_str());
		}
		else if (Response.has_entity())
		{
			FString Key = KeyOfMessage(Response.entity());
			ChangedKeys.Add(Key);
			FSpeechlyResponse& Out = Responses.FindOrAdd(Key);
			FString Entity = Response.entity().entity().c_str();
			FString Value = Response.entity().value().c_str();
			Out.Entities.Emplace(Entity, Value);
		}
		else if (Response.has_intent())
		{
			FString Key = KeyOfMessage(Response.intent());
			ChangedKeys.Add(Key);
			FSpeechlyResponse& Out = Responses.FindOrAdd(Key);
			Out.Intent = Response.intent().intent().c_str();
		}
		else if (Response.has_segment_end())
		{
			FString Key = KeyOfMessage(Response.intent());
			ChangedKeys.Add(Key);
			FSpeechlyResponse& Out = Responses.FindOrAdd(Key);
			Out.bIsFinal = true;
		}
	}

	for (const FString& Key : ChangedKeys)
	{
		FSpeechlyResponse* ChangedResponse = Responses.Find(Key);
		if (ChangedResponse != nullptr)
		{
			OnSpeechlyResponse.Broadcast(Key, *ChangedResponse);
		}
	}

	for (const FString& Context : FinishedContexts)
	{
		TSet<FString>* Contexts = ContextToKeys.Find(Context);
		if (Contexts != nullptr)
		{
			for (const FString& Key : *Contexts)
			{
				Responses.Remove(Key);
			}
		}
		ContextToKeys.Remove(Context);
	}

	for (const auto& Entry : Errors)
	{
		OnSpeechlyError.Broadcast(Entry.Key, Entry.Value);
	}
	return true;
}

void USpeechly::OnSpeechAudio(const float* Audio, const int32 AudioLength)
{
 	if (!IsConnected() || AudioLength == 0)
	{
		return;
	}
	int32 OutputAudioLength = AudioLength * 2; // 16-bit samples in 8-bit char
	if (CharAudio.Num() < OutputAudioLength)
	{
		CharAudio.SetNumUninitialized(OutputAudioLength);
	}
	bool bHasAudio = false;
	uint16* ShortAudio = reinterpret_cast<uint16*>(CharAudio.GetData());
	for (int32 i = 0; i < AudioLength; ++i)
	{
		if (Audio[i] != 0.f)
		{
			bHasAudio = true;
		}
		int32 ScaledSample = static_cast<int32>(Audio[i] * (Audio[i] < 0.f ? 32768.f : 32767.f));
		ScaledSample = FPlatformMath::Max(-32768, FPlatformMath::Min(32767, ScaledSample));
		int16 Sample = static_cast<int16>(ScaledSample);
		ShortAudio[i] = Sample;
	}

	if (bHasAudio)
	{
		SilenceCount = 0;
	}
	else
	{
		SilenceCount += AudioLength;
		if (SilenceCount > sg::kSampleRate * 5)
		{
			UE_LOG(LogSG, Warning, TEXT("Recorder complete silence for a while, check your default audio device"));
			SilenceCount = 0;
		}
	}

	// Waiting to receive start, don't send audio
	if (bIsBuffering)
	{
		AudioBuffer.Append(CharAudio.GetData(), OutputAudioLength);
	}
	else
	{
		// There is a buffer to send, send that
		if (AudioBuffer.Num() != 0)
		{
			AudioBuffer.Append(CharAudio.GetData(), OutputAudioLength);
			SLURequest Request;
			Request.set_audio(AudioBuffer.GetData(), AudioBuffer.Num());
			Client->Write(Request);
			AudioBuffer.Empty();
		}
		else
		{
			SLURequest Request;
			Request.set_audio(CharAudio.GetData(), OutputAudioLength);
			Client->Write(Request);
		}
	}
}
