#pragma once

#include "CoreMinimal.h"
#include "AudioCapture.h"
#include "HAL/RunnableThread.h"
#include "Runnable.h"
#include "LogMacros.h"
#include "Containers/Queue.h"

#include <memory>
#include <string>

#include "IncludeBegin.h"
THIRD_PARTY_INCLUDES_START
#include "grpc++/grpc++.h"
#include "sg.grpc.pb.h"
THIRD_PARTY_INCLUDES_END
#include "IncludeEnd.h"

#include "Speechgrinder.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSG, Log, All);

using namespace speechgrinder::sgapi::v1;
using namespace Audio;

// GRPC threaded client
class SPEECHGRINDER_API SpeechgrinderClient : public FRunnable
{
public:
    SpeechgrinderClient(const std::string& Address, const std::string& DeviceId, const std::string& AppId, const std::string& LanguageCode);
    bool Write(const SluRequest& Request);
    bool Read(SluResponse& OutResponse);
    bool HasError() const
    {
        return bHasError;
    }
    
    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Exit() override;
    virtual void Stop() override;

private:
	// GRPC abstractions
	bool CanWrite();
	bool CanRead();
	void StreamWrite(const SluRequest& Request);
	void StreamRead(SluResponse* OutResponse);
	void HandleTag(void* Tag);
	void SetError(const FString& Message);

private:
    std::string Address;
    std::string DeviceId;
    std::string AppId;
    std::string LanguageCode;
    std::shared_ptr<grpc::ChannelCredentials> Credentials;
	std::shared_ptr<grpc::Channel> Channel;
    std::unique_ptr<Slu::Stub> SluStub;
    std::unique_ptr<grpc::ClientAsyncReaderWriterInterface<SluRequest, SluResponse>> Stream;

    // GRPC shared state to be able to cleanup memory used in Run() at Exit()
    // Otherwise not meant to be used outside of Run()
    grpc::ClientContext Context;
    grpc::CompletionQueue CompletionQueue;
    uintptr_t Seq{0};
    uintptr_t LastWriteSeq{0};
    uintptr_t LastReadSeq{0};
    bool bWriteAllowed{true};
    bool bReadAllowed{true};
    SluResponse Response;

    bool bIsRunning{true};
    bool bHasError{false};
    TQueue<SluRequest, EQueueMode::Mpsc> RequestQueue;
    TQueue<SluResponse, EQueueMode::Mpsc> ResponseQueue;
};

class ISpeechAudioCallback
{
public:
	virtual void OnSpeechAudio(const float* Audio, const int32 AudioLength) = 0;
	virtual ~ISpeechAudioCallback() {}
};

// Audio recorder with downsampling to 8000hz
class FSpeechRecorder : public IAudioCaptureCallback
{
public:
    FSpeechRecorder();
    virtual ~FSpeechRecorder();
    void Start();
    void Stop();

    virtual void OnAudioCapture(float* AudioData, int32 NumFrames, int32 NumChannels, double StreamTime, bool bOverflow) override;
	ISpeechAudioCallback* Callback;

private:
	void generateFilter();

	TArray<float> Filter;
	float SampleRatio;
	TArray<float> Buffer;
	TArray<float> Output;
    bool bIsCapturing{false};
    FAudioCapture AudioCapture;
    FCaptureDeviceInfo OutInfo;
    FCriticalSection CriticalSection;

};

USTRUCT(BlueprintType)
struct FSpeechgrinderToken
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Text;

	UPROPERTY(BlueprintReadOnly)
	FString TextWithTrailingSpace;

	UPROPERTY(BlueprintReadOnly)
	FString Lemma;

	UPROPERTY(BlueprintReadOnly)
	FString Pos;

	UPROPERTY(BlueprintReadOnly)
	FString Tag;

	UPROPERTY(BlueprintReadOnly)
	FString Case;

	UPROPERTY(BlueprintReadOnly)
	FString Number;

	UPROPERTY(BlueprintReadOnly)
	FString EntityType;

	UPROPERTY(BlueprintReadOnly)
	int32 PositionInEntity; // outsideOf = 0; startOf = 1; insideOf = 2;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSegmentStart;

	UPROPERTY(BlueprintReadOnly)
	int32 TrailingSilence;
};

USTRUCT(BlueprintType)
struct FSpeechgrinderAlternative
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float Confidence;

	UPROPERTY(BlueprintReadOnly)
	TArray<FSpeechgrinderToken> Tokens;
};

USTRUCT(BlueprintType)
struct FSpeechgrinderUtterance
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bIsFinal;

	UPROPERTY(BlueprintReadOnly)
	TArray<FSpeechgrinderAlternative> Alternatives;
};

UENUM()
enum class ESpeechgrinderResponseType : uint8
{
	Started, Utterance, Finished, Unknown
};

USTRUCT(BlueprintType)
struct FSpeechgrinderResponse
{
    GENERATED_BODY()
    
	UPROPERTY(BlueprintReadOnly)
	ESpeechgrinderResponseType Event;

	UPROPERTY(BlueprintReadOnly)
	FString UtteranceId;

	UPROPERTY(BlueprintReadOnly)
	bool bHasError;

	UPROPERTY(BlueprintReadOnly)
	FString ErrorCode;

	UPROPERTY(BlueprintReadOnly)
	FString ErrorMessage;

	UPROPERTY(BlueprintReadOnly)
	FSpeechgrinderUtterance Utterance;
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
	void Connect(const FString& DeviceId, const FString& AppId, const FString& LanguageCode);
    
	/** Start a new Speechgrinder utterance */
    UFUNCTION(BlueprintCallable)
    bool Start();

	/** Stop the current Speechgrinder utterance */
    UFUNCTION(BlueprintCallable)
    bool Stop();

	/** Read Speechgrinder results, if there are any */
    UFUNCTION(BlueprintCallable)
    bool Read(FSpeechgrinderResponse& OutSpeechgrinderResponse, bool& OutError);
    
	/** Returns true if connected to Speechgrinder */
	UFUNCTION(BlueprintCallable)
	bool isConnected() const {
		return Client.IsValid() && !Client->HasError();
	}

private:
	FString LastUtteranceId;
	TUniquePtr<SpeechgrinderClient> Client;
    FRunnableThread* ClientThread;
    FSpeechRecorder Recorder;
	TArray<char> CharAudio; // as a field to reduce allocations

	// Inherited via ISpeechAudioCallback
	virtual void OnSpeechAudio(const float* Audio, const int32 AudioLength) override;
};
