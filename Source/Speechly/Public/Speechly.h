#pragma once

#include "SpeechlyClient.h"
#include "SpeechRecorder.h"

#include "CoreMinimal.h"
#include "HAL/RunnableThread.h"
#include "LogMacros.h"

#include "Speechly.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSG, Log, All);

// Can't use an anonymous namespace because of Unity build
namespace sg {
	static const int kSampleRate = 16000;
	static const int kNumFramesDesired = 1024;
};

USTRUCT(BlueprintType)
struct FSpeechlyResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Transcript;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> Entities;

	UPROPERTY(BlueprintReadOnly)
	FString Intent;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFinal;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpeechlyResponse, FString, Key, FSpeechlyResponse, Response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpeechlyError, FString, Key, FString, Error);

/**
 * UE4 specific wrapper for Speechly SLU
 *
 * Call Connect(DeviceId, AppId, LanguageCode) first to create a network connection.
 * 
 * Start() and Stop() are called to start a new recording and stop the current recording.
 * Audio is sent automatically when recording is enabled.
 *
 * To fetch results call Read(), it fills the results in an output parameter, and returns
 * an boolean if there were any results. There can be multiple results in a queue. To
 * read everything call Read() until it returns False.
 */
UCLASS(Blueprintable)
class SPEECHLY_API USpeechly : public UObject, public ISpeechAudioCallback
{
	GENERATED_BODY()

public:
	USpeechly();
	virtual ~USpeechly();

	UFUNCTION(Category = "Speechly", BlueprintCallable)
	static USpeechly* SpawnSpeechly()
    {
		return NewObject<USpeechly>(USpeechly::StaticClass());
	}

	/** Connect to Speechly, must be called before other functions */
	UFUNCTION(Category = "Speechly", BlueprintCallable)
	void Connect(const FString& AppId, const FString& LanguageCode);
    
	/** Start a new Speechly utterance */
    UFUNCTION(Category = "Speechly", BlueprintCallable)
    bool Start();

	/** Stop the current Speechly utterance */
    UFUNCTION(Category = "Speechly", BlueprintCallable)
    bool Stop();

	/** Returns true if connected to Speechly */
	UFUNCTION(Category = "Speechly", BlueprintCallable)
	bool IsConnected() const;

	/** Send text to Speechly (call is blocking and only meant for testing)
	
	Results are returned from the OnSpeechlyResponse delegate. */
	UFUNCTION(Category = "Speechly", BlueprintCallable)
	void SendText(const FString& Text);

private:
	bool Tick(float DeltaTime);

	template <typename T>
	FString KeyOfMessage(const T& Message)
	{
		FString Key = FString::Printf(TEXT("%s-%i"), *FString(Message.audio_context().c_str()), Message.segment_id());
		ContextToKeys.FindOrAdd(Message.audio_context().c_str()).Add(Key);
		return Key;
	}

public:
	UPROPERTY(Category = "Speechly", BlueprintAssignable)
	FOnSpeechlyResponse OnSpeechlyResponse;

	UPROPERTY(Category = "Speechly", BlueprintAssignable)
	FOnSpeechlyError OnSpeechlyError;

private:
	FDelegateHandle TickerHandle;
	FString LastAudioContext;
	TUniquePtr<SpeechlyClient> Client;
    FRunnableThread* ClientThread;
	FSpeechRecorder Recorder{1024, 16000};
	TArray<char> CharAudio; // as a field to reduce allocations
	TArray<char> AudioBuffer; // Used to buffer start of audio until server is ready
	bool bIsBuffering;
	int32 SilenceCount = 0;
	TMap<FString, FSpeechlyResponse> Responses;
	TMap<FString, TSet<FString>> ContextToKeys;

	// Inherited via ISpeechAudioCallback
	virtual void OnSpeechAudio(const float* Audio, const int32 AudioLength) override;
};
