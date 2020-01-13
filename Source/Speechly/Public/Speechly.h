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
struct FSpeechlyTranscript
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 SegmentId;

	UPROPERTY(BlueprintReadOnly)
	FString Word;

	UPROPERTY(BlueprintReadOnly)
	int32 Index;

	UPROPERTY(BlueprintReadOnly)
	int32 StartTime;

	UPROPERTY(BlueprintReadOnly)
	int32 EndTime;
};

USTRUCT(BlueprintType)
struct FSpeechlyEntity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 SegmentId;

	UPROPERTY(BlueprintReadOnly)
	FString Entity;

	UPROPERTY(BlueprintReadOnly)
	FString Value;

	UPROPERTY(BlueprintReadOnly)
	int32 StartPosition;

	UPROPERTY(BlueprintReadOnly)
	int32 EndPosition;
};

USTRUCT(BlueprintType)
struct FSpeechlyIntent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 SegmentId;

	UPROPERTY(BlueprintReadOnly)
	FString Intent;
};

USTRUCT(BlueprintType)
struct FSpeechlySegmentEnd
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 SegmentId;
};

UENUM(BlueprintType)
enum class ESpeechlyResponseType : uint8
{
	Started, Transcript, Entity, Intent, SegmentEnd, Finished, Unknown
};

USTRUCT(BlueprintType)
struct FSpeechlyResponse
{
    GENERATED_BODY()
    
	UPROPERTY(BlueprintReadOnly)
	ESpeechlyResponseType Event;

	UPROPERTY(BlueprintReadOnly)
	FString AudioContext;

	UPROPERTY(BlueprintReadOnly)
	bool bHasError;

	UPROPERTY(BlueprintReadOnly)
	FString ErrorCode;

	UPROPERTY(BlueprintReadOnly)
	FString ErrorMessage;

	UPROPERTY(BlueprintReadOnly)
	FSpeechlyTranscript Transcript;

	UPROPERTY(BlueprintReadOnly)
	FSpeechlyEntity Entity;

	UPROPERTY(BlueprintReadOnly)
	FSpeechlyIntent Intent;

	UPROPERTY(BlueprintReadOnly)
	FSpeechlySegmentEnd SegmentEnd;
};

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

	UFUNCTION(BlueprintCallable)
	static USpeechly* SpawnSpeechly()
    {
		return NewObject<USpeechly>(USpeechly::StaticClass());
	}

	/** Connect to Speechly, must be called before other functions */
	UFUNCTION(BlueprintCallable)
	void Connect(const FString& AppId, const FString& LanguageCode);
    
	/** Start a new Speechly utterance */
    UFUNCTION(BlueprintCallable)
    bool Start();

	/** Stop the current Speechly utterance */
    UFUNCTION(BlueprintCallable)
    bool Stop();

	/** Read Speechly results, if there are any */
    UFUNCTION(BlueprintCallable)
    bool Read(FSpeechlyResponse& OutSpeechlyResponse, bool& OutError);

	/** Returns true if connected to Speechly */
	UFUNCTION(BlueprintCallable)
	bool IsConnected() const;

private:
	FString LastAudioContext;
	TUniquePtr<SpeechlyClient> Client;
    FRunnableThread* ClientThread;
	FSpeechRecorder Recorder{1024, 16000};
	TArray<char> CharAudio; // as a field to reduce allocations
	TArray<char> AudioBuffer; // Used to buffer start of audio until server is ready
	bool bIsBuffering;

	// Inherited via ISpeechAudioCallback
	virtual void OnSpeechAudio(const float* Audio, const int32 AudioLength) override;

	void DrainBuffer();
};
