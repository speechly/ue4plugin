#include "SpeechlyClient.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

SpeechlyClient::SpeechlyClient(const std::string& Address, const std::string& DeviceId, const std::string& AppId, const std::string& LanguageCode, int SampleRate) : Address{ Address }, DeviceId{ DeviceId }, AppId{ AppId }, LanguageCode{ LanguageCode }, SampleRate{ SampleRate }
{
	FString Pem;
	FString PemPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()).Append(TEXT("NonUFS/roots.pem"));
	if (FFileHelper::LoadFileToString(Pem, *PemPath, {}))
	{
		Credentials = grpc::SslCredentials(grpc::SslCredentialsOptions{ std::string(TCHAR_TO_UTF8(*Pem)) });
	}
	else
	{
		UE_LOG(LogSG, Error, TEXT("Could not read '%s' for root certificates, using system certificates which probably won't work."), *PemPath);
		Credentials = grpc::SslCredentials(grpc::SslCredentialsOptions{});
	}
}

bool SpeechlyClient::Write(const SLURequest& Request)
{
	if (bHasError || !bIsRunning)
	{
		UE_LOG(LogSG, Error, TEXT("Tried to write to SpeechlyClient that is not running"));
		return false;
	}
	return RequestQueue.Enqueue(Request);
}

bool SpeechlyClient::Read(SLUResponse& OutResponse)
{
	if (bHasError || !bIsRunning)
	{
		UE_LOG(LogSG, Error, TEXT("Tried to read from SpeechlyClient that is not running"));
		return false;
	}
	return ResponseQueue.Dequeue(OutResponse);
}

bool SpeechlyClient::Init()
{
	Channel = grpc::CreateChannel(Address, Credentials);

	auto IdentityStub = Identity::NewStub(Channel);

	grpc::ClientContext IdentityContext;

	LoginRequest Request;
	Request.set_device_id(DeviceId);
	Request.set_app_id(AppId);
	LoginResponse LoginResponse;

	grpc::Status Status = IdentityStub->Login(&IdentityContext, Request, &LoginResponse);
	if (!Status.ok())
	{
		UE_LOG(LogSG, Error, TEXT("Could not call login"));
		SetError("Could not login");
		Channel.reset();
		return false;
	}
	Context.AddMetadata("authorization", "Bearer " + LoginResponse.token());
	return true;
}

uint32 SpeechlyClient::Run()
{
	SLUStub = SLU::NewStub(Channel);

	uintptr_t StreamSeq = ++Seq;
	Stream = SLUStub->AsyncStream(&Context, &CompletionQueue, reinterpret_cast<void*>(StreamSeq));

	// Wait for Stream to open
	{
		void* Tag;
		bool Ok;
		if (CompletionQueue.Next(&Tag, &Ok))
		{
			if (!Ok || Tag != reinterpret_cast<void*>(StreamSeq))
			{
				UE_LOG(LogSG, Error, TEXT("Unexpected Stream open"));
				bHasError = true;
				return 1;
			}
		}
		else
		{
			UE_LOG(LogSG, Error, TEXT("Stream prematurely shut down"));
			bHasError = true;
			return 1;
		}
	}

	// Configure stream
	{
		SLURequest Request;
		SLUConfig* Config = Request.mutable_config();
		Config->set_channels(1);
		Config->set_sample_rate_hertz(SampleRate);
		Config->set_language_code(LanguageCode);

		StreamWrite(Request);
		void* Tag;
		bool Ok;
		if (CompletionQueue.Next(&Tag, &Ok))
		{
			HandleTag(Tag);
			if (!Ok || Tag != reinterpret_cast<void*>(LastWriteSeq))
			{
				SetError("Could not configure stream");
				return 1;
			}
		}
		else
		{
			SetError("Stream error");
			return 1;
		}
	}

	while (bIsRunning && !bHasError)
	{
		if (CanWrite())
		{
			SLURequest Request;
			if (RequestQueue.Dequeue(Request))
			{
				StreamWrite(Request);
			}
		}
		if (CanRead())
		{
			StreamRead(&Response);
		}

		void* Tag;
		bool Ok;
		gpr_timespec Deadline = gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC), gpr_time_from_millis(2, GPR_TIMESPAN));
		grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
		if (NextStatus == grpc::CompletionQueue::GOT_EVENT)
		{
			HandleTag(Tag);
			if (Tag == reinterpret_cast<void*>(LastWriteSeq))
			{
				if (!Ok)
				{
					SetError("Speechly Write failed");
					return 1;
				}
			}
			else if (Tag == reinterpret_cast<void*>(LastReadSeq))
			{
				if (!Ok)
				{
					SetError("Speechly Read failed");
					return 1;
				}
				else
				{
					ResponseQueue.Enqueue(Response);
				}
			}
			else
			{
				UE_LOG(LogSG, Warning, TEXT("Speechly unknown tag"));
				if (!Ok)
				{
					SetError("Unknown tag with an error");
					return 1;
				}
			}
		}
		else if (NextStatus == grpc::CompletionQueue::TIMEOUT)
		{
			// Noop
		}
		else if (NextStatus == grpc::CompletionQueue::SHUTDOWN)
		{
			bIsRunning = false;
			break;
		}
	}

	return 0;
}

void SpeechlyClient::Exit()
{
	if (Stream)
	{
		gpr_timespec Deadline = gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC), gpr_time_from_seconds(5, GPR_TIMESPAN));

		// GRPC shutdown from client side is a complicated system,
		// the following code is based on this understanding:
		// - Context cancellation races with reads, so read until it fails
		// - Stream can only be finished if there are no reads and writes pending
		// - Stream finishes requires server status (eg. cancel or close)
		// - CompletionQueue must be shutdown
		// - CQ can only be shutdown after the queue is drained
		// - CQ shutdown cannot be started if we are enqueueing requests

		// Activate cancellation as we don't want to wait for server to close the connection
		// But if we have already errored out, don't cancel so we can get the status
		if (!bHasError)
		{
			Context.TryCancel();
		}

		// Drain requests and launch reads until stopped from cancellation
		while (true)
		{
			if (CanRead())
			{
				StreamRead(&Response);
			}

			void* Tag;
			bool Ok;
			grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
			if (NextStatus == grpc::CompletionQueue::GOT_EVENT)
			{
				HandleTag(Tag);
				if (!Ok)
				{
					break;
				}
			}
			else
			{
				UE_LOG(LogSG, Warning, TEXT("Timed out or shutdown while waiting for cancellation"));
				break;
			}
		}

		// Finish the stream
		grpc::Status Status;
		uintptr_t FinishDoneSeq;
		Stream->Finish(&Status, reinterpret_cast<void*>(FinishDoneSeq = ++Seq));
		while (true)
		{
			void* Tag;
			bool Ok;
			grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
			if (NextStatus == grpc::CompletionQueue::GOT_EVENT)
			{
				if (Tag == reinterpret_cast<void*>(FinishDoneSeq) || !Ok)
				{
					break;
				}
				UE_LOG(LogSG, Warning, TEXT("Received unknown tag when waiting for finish"));
			}
			else if (NextStatus == grpc::CompletionQueue::TIMEOUT)
			{
				UE_LOG(LogSG, Warning, TEXT("Speechly finish timed out, this can result in a memory leak"));
				break;
			}
			else if (NextStatus == grpc::CompletionQueue::SHUTDOWN)
			{
				break;
			}
		}

		if (bHasError && !Status.ok())
		{
			FString Message = Status.error_message().c_str();
			UE_LOG(LogSG, Error, TEXT("Speechly non-ok exit status: '%s'"), *Message);
		}

		CompletionQueue.Shutdown();
		while (true)
		{
			void* Tag;
			bool Ok;
			grpc::CompletionQueue::NextStatus NextStatus = CompletionQueue.AsyncNext(&Tag, &Ok, Deadline);
			if (NextStatus == grpc::CompletionQueue::TIMEOUT)
			{
				UE_LOG(LogSG, Warning, TEXT("Speechly shutdown timed out, this can result in a memory leak"));
				return;
			}
			else if (NextStatus == grpc::CompletionQueue::SHUTDOWN)
			{
				// Drained and shutdown
				return;
			}
		}
	}
}

void SpeechlyClient::Stop()
{
	bIsRunning = false;
}

bool SpeechlyClient::CanWrite()
{
	return bWriteAllowed;
}

bool SpeechlyClient::CanRead()
{
	return bReadAllowed;
}

void SpeechlyClient::StreamWrite(const SLURequest& Request)
{
	check(Stream);
	check(CanWrite());
	Stream->Write(Request, reinterpret_cast<void*>(LastWriteSeq = ++Seq));
	bWriteAllowed = false;
}

void SpeechlyClient::StreamRead(SLUResponse* OutResponse)
{
	check(Stream);
	check(CanRead());
	Stream->Read(OutResponse, reinterpret_cast<void*>(LastReadSeq = ++Seq));
	bReadAllowed = false;
}

void SpeechlyClient::HandleTag(void* Tag)
{
	if (Tag == reinterpret_cast<void*>(LastWriteSeq))
	{
		bWriteAllowed = true;
	}
	else if (Tag == reinterpret_cast<void*>(LastReadSeq))
	{
		bReadAllowed = true;
	}
}

void SpeechlyClient::SetError(const FString& Message)
{
	UE_LOG(LogSG, Error, TEXT("%s"), *Message);
	bHasError = true;
	bIsRunning = false;
}
