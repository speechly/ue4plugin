#pragma once

#include "CoreMinimal.h"
#include "Runnable.h"
#include "Containers/Queue.h"

#include <memory>
#include <string>

#include "IncludeBegin.h"
THIRD_PARTY_INCLUDES_START
#include "grpc++/grpc++.h"
#include "sg.grpc.pb.h"
THIRD_PARTY_INCLUDES_END
#include "IncludeEnd.h"

using namespace speechgrinder::sgapi::v1;

// GRPC threaded client
class SPEECHGRINDER_API SpeechgrinderClient : public FRunnable
{
public:
	SpeechgrinderClient(const std::string& Address, const std::string& DeviceId, const std::string& AppId, const std::string& LanguageCode, int SampleRate);
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
	int SampleRate;
	std::shared_ptr<grpc::ChannelCredentials> Credentials;
	std::shared_ptr<grpc::Channel> Channel;
	std::unique_ptr<Slu::Stub> SluStub;
	std::unique_ptr<grpc::ClientAsyncReaderWriterInterface<SluRequest, SluResponse>> Stream;

	// GRPC shared state to be able to cleanup memory used in Run() at Exit()
	// Otherwise not meant to be used outside of Run()
	grpc::ClientContext Context;
	grpc::CompletionQueue CompletionQueue;
	uintptr_t Seq{ 0 };
	uintptr_t LastWriteSeq{ 0 };
	uintptr_t LastReadSeq{ 0 };
	bool bWriteAllowed{ true };
	bool bReadAllowed{ true };
	SluResponse Response;

	bool bIsRunning{ true };
	bool bHasError{ false };
	TQueue<SluRequest, EQueueMode::Mpsc> RequestQueue;
	TQueue<SluResponse, EQueueMode::Mpsc> ResponseQueue;
};