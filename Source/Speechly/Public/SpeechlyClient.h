#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Containers/Queue.h"

#include <memory>
#include <string>

#include "IncludeBegin.h"
THIRD_PARTY_INCLUDES_START
#include "grpc++/grpc++.h"
#include "speechly/identity/v1/identity.grpc.pb.h"
#include "speechly/slu/v1/slu.grpc.pb.h"
#include "speechly/slu/v1/wlu.grpc.pb.h"
THIRD_PARTY_INCLUDES_END
#include "IncludeEnd.h"

using namespace speechly::identity::v1;
using namespace speechly::slu::v1;

// GRPC threaded client
class SPEECHLY_API SpeechlyClient : public FRunnable
{
public:
	SpeechlyClient(const std::string& Address, const std::string& DeviceId, const std::string& AppId, const std::string& LanguageCode, int SampleRate);
	bool Write(const SLURequest& Request);
	bool Read(SLUResponse& OutResponse);
	bool HasError() const
	{
		return bHasError;
	}
    FString GetError() const
    {
        return ErrorMessage;
    }
	bool WLUSync(const std::string& Text);

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

private:
	// GRPC abstractions
	bool CanWrite();
	bool CanRead();
	void StreamWrite(const SLURequest& Request);
	void StreamRead(SLUResponse* OutResponse);
	void HandleTag(void* Tag);
	void SetError(const FString& Message);

private:
	std::string LoginToken;
	std::string Address;
	std::string DeviceId;
	std::string AppId;
	std::string LanguageCode;
	int SampleRate;
	std::shared_ptr<grpc::ChannelCredentials> Credentials;
	std::shared_ptr<grpc::Channel> Channel;
	std::unique_ptr<SLU::Stub> SLUStub;
	std::unique_ptr<grpc::ClientAsyncReaderWriterInterface<SLURequest, SLUResponse>> Stream;

	// GRPC shared state to be able to cleanup memory used in Run() at Exit()
	// Otherwise not meant to be used outside of Run()
	grpc::ClientContext Context;
	grpc::CompletionQueue CompletionQueue;
	uintptr_t Seq{ 0 };
	uintptr_t LastWriteSeq{ 0 };
	uintptr_t LastReadSeq{ 0 };
	bool bWriteAllowed{ true };
	bool bReadAllowed{ true };
	SLUResponse Response;

	bool bIsRunning{ true };
	bool bHasError{ false };
    FString ErrorMessage;
	TQueue<SLURequest, EQueueMode::Mpsc> RequestQueue;
	TQueue<SLUResponse, EQueueMode::Mpsc> ResponseQueue;
};
