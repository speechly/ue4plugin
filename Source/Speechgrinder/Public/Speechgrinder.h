#pragma once

#include "SpeechgrinderClient.h"
#include "SpeechRecorder.h"

#include "CoreMinimal.h"
#include "HAL/RunnableThread.h"
#include "LogMacros.h"

#include "Speechgrinder.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSG, Log, All);

// Can't use an anonymous namespace because of Unity build
namespace sg {
	static const int kSampleRate = 16000;
	static const int kNumFramesDesired = 1024;
};

USTRUCT(BlueprintType)
struct FSpeechgrinderTranscript
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

UENUM()
enum class ESpeechgrinderResponseType : uint8
{
	Started, Transcript, Finished, Unknown
};

USTRUCT(BlueprintType)
struct FSpeechgrinderResponse
{
    GENERATED_BODY()
    
	UPROPERTY(BlueprintReadOnly)
	ESpeechgrinderResponseType Event;

	UPROPERTY(BlueprintReadOnly)
	FString AudioContext;

	UPROPERTY(BlueprintReadOnly)
	bool bHasError;

	UPROPERTY(BlueprintReadOnly)
	FString ErrorCode;

	UPROPERTY(BlueprintReadOnly)
	FString ErrorMessage;

	UPROPERTY(BlueprintReadOnly)
	FSpeechgrinderTranscript Transcript;
};

/**
 * UE4 specific wrapper for Speechgrinder SLU
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
class SPEECHGRINDER_API USpeechgrinder : public UObject, public ISpeechAudioCallback
{
	GENERATED_BODY()

public:
	USpeechgrinder();
	virtual ~USpeechgrinder();

	UFUNCTION(BlueprintCallable)
	static USpeechgrinder* SpawnSpeechgrinder()
    {
		return NewObject<USpeechgrinder>(USpeechgrinder::StaticClass());
	}

	/** Connect to Speechgrinder, must be called before other functions */
	UFUNCTION(BlueprintCallable)
	void Connect(const FString& AppId, const FString& LanguageCode);
    
	/** Start a new Speechgrinder utterance */
    UFUNCTION(BlueprintCallable)
    bool Start();

	/** Stop the current Speechgrinder utterance */
    UFUNCTION(BlueprintCallable)
    bool Stop();

	/** Read Speechgrinder results, if there are any */
    UFUNCTION(BlueprintCallable)
    bool Read(FSpeechgrinderResponse& OutSpeechgrinderResponse, bool& OutError);

	/** Read the latest Speechgrinder results, if there is any */
	UFUNCTION(BlueprintCallable)
	void ReadLatestResults(TArray<FSpeechgrinderResponse>& OutSpeechgrinderResponses, bool& OutError);

	/** Returns true if connected to Speechgrinder */
	UFUNCTION(BlueprintCallable)
	bool IsConnected() const;

private:
	FString LastAudioContext;
	TUniquePtr<SpeechgrinderClient> Client;
    FRunnableThread* ClientThread;
	FSpeechRecorder Recorder{1024, 16000};
	TArray<char> CharAudio; // as a field to reduce allocations
	TArray<char> AudioBuffer; // Used to buffer start of audio until server is ready
	bool bIsBuffering;

	// Inherited via ISpeechAudioCallback
	virtual void OnSpeechAudio(const float* Audio, const int32 AudioLength) override;

	void DrainBuffer();
};
