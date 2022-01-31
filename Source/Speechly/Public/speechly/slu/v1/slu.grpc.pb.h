// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: speechly/slu/v1/slu.proto
#ifndef GRPC_speechly_2fslu_2fv1_2fslu_2eproto__INCLUDED
#define GRPC_speechly_2fslu_2fv1_2fslu_2eproto__INCLUDED

#include "speechly/slu/v1/slu.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc_impl {
class CompletionQueue;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc_impl

namespace grpc {
namespace experimental {
template <typename RequestT, typename ResponseT>
class MessageAllocator;
}  // namespace experimental
}  // namespace grpc

namespace speechly {
namespace slu {
namespace v1 {

// Service that implements Speechly SLU (Spoken Language Understanding) API.
//
// To use this service you MUST use an access token from Speechly Identity API.
// The token MUST be passed in gRPC metadata with `Authorization` key and `Bearer ACCESS_TOKEN` as value, e.g. in Go:
//
// ```
// ctx := context.Background()
// ctx = metadata.AppendToOutgoingContext(ctx, "Authorization", "Bearer "+accessToken)
// stream, err := speechlySLUClient.Stream(ctx)
// ```
class SLU final {
 public:
  static constexpr char const* service_full_name() {
    return "speechly.slu.v1.SLU";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Performs bidirectional streaming speech recognition: receive results while sending audio.
    //
    // First request MUST be an SLUConfig message with the configuration that describes the audio format being sent.
    //
    // This RPC can handle multiple logical audio segments with the use of `SLUEvent_START` and `SLUEvent_STOP` messages,
    // which are used to indicate the beginning and the end of a segment.
    //
    // A typical call timeline will look like this:
    //
    // 1. Client starts the RPC.
    // 2. Client sends `SLUConfig` message with audio configuration.
    // 3. Client sends `SLUEvent.START`.
    // 4. Client sends audio and receives responses from the server.
    // 5. Client sends `SLUEvent.STOP`.
    // 6. Client sends `SLUEvent.START`.
    // 7. Client sends audio and receives responses from the server.
    // 8. Client sends `SLUEvent.STOP`.
    // 9. Client closes the stream and receives responses from the server until EOF is received.
    //
    // NB: the client does not have to wait until the server acknowledges the start / stop events,
    // this is done asynchronously. The client can deduplicate responses based on the audio context ID,
    // which will be present in every response message.
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>> Stream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>>(StreamRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>> AsyncStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>>(AsyncStreamRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>> PrepareAsyncStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>>(PrepareAsyncStreamRaw(context, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      // Performs bidirectional streaming speech recognition: receive results while sending audio.
      //
      // First request MUST be an SLUConfig message with the configuration that describes the audio format being sent.
      //
      // This RPC can handle multiple logical audio segments with the use of `SLUEvent_START` and `SLUEvent_STOP` messages,
      // which are used to indicate the beginning and the end of a segment.
      //
      // A typical call timeline will look like this:
      //
      // 1. Client starts the RPC.
      // 2. Client sends `SLUConfig` message with audio configuration.
      // 3. Client sends `SLUEvent.START`.
      // 4. Client sends audio and receives responses from the server.
      // 5. Client sends `SLUEvent.STOP`.
      // 6. Client sends `SLUEvent.START`.
      // 7. Client sends audio and receives responses from the server.
      // 8. Client sends `SLUEvent.STOP`.
      // 9. Client closes the stream and receives responses from the server until EOF is received.
      //
      // NB: the client does not have to wait until the server acknowledges the start / stop events,
      // this is done asynchronously. The client can deduplicate responses based on the audio context ID,
      // which will be present in every response message.
      virtual void Stream(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::speechly::slu::v1::SLURequest,::speechly::slu::v1::SLUResponse>* reactor) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>* StreamRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>* AsyncStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>* PrepareAsyncStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    std::unique_ptr< ::grpc::ClientReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>> Stream(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>>(StreamRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>> AsyncStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>>(AsyncStreamRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>> PrepareAsyncStream(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>>(PrepareAsyncStreamRaw(context, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void Stream(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::speechly::slu::v1::SLURequest,::speechly::slu::v1::SLUResponse>* reactor) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>* StreamRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>* AsyncStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>* PrepareAsyncStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Stream_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Performs bidirectional streaming speech recognition: receive results while sending audio.
    //
    // First request MUST be an SLUConfig message with the configuration that describes the audio format being sent.
    //
    // This RPC can handle multiple logical audio segments with the use of `SLUEvent_START` and `SLUEvent_STOP` messages,
    // which are used to indicate the beginning and the end of a segment.
    //
    // A typical call timeline will look like this:
    //
    // 1. Client starts the RPC.
    // 2. Client sends `SLUConfig` message with audio configuration.
    // 3. Client sends `SLUEvent.START`.
    // 4. Client sends audio and receives responses from the server.
    // 5. Client sends `SLUEvent.STOP`.
    // 6. Client sends `SLUEvent.START`.
    // 7. Client sends audio and receives responses from the server.
    // 8. Client sends `SLUEvent.STOP`.
    // 9. Client closes the stream and receives responses from the server until EOF is received.
    //
    // NB: the client does not have to wait until the server acknowledges the start / stop events,
    // this is done asynchronously. The client can deduplicate responses based on the audio context ID,
    // which will be present in every response message.
    virtual ::grpc::Status Stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::speechly::slu::v1::SLUResponse, ::speechly::slu::v1::SLURequest>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_Stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Stream() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::speechly::slu::v1::SLUResponse, ::speechly::slu::v1::SLURequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestStream(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::speechly::slu::v1::SLUResponse, ::speechly::slu::v1::SLURequest>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Stream<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_Stream() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc_impl::internal::CallbackBidiHandler< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>(
          [this] { return this->Stream(); }));
    }
    ~ExperimentalWithCallbackMethod_Stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::speechly::slu::v1::SLUResponse, ::speechly::slu::v1::SLURequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::experimental::ServerBidiReactor< ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>* Stream() {
      return new ::grpc_impl::internal::UnimplementedBidiReactor<
        ::speechly::slu::v1::SLURequest, ::speechly::slu::v1::SLUResponse>;}
  };
  typedef ExperimentalWithCallbackMethod_Stream<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Stream() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::speechly::slu::v1::SLUResponse, ::speechly::slu::v1::SLURequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_Stream() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::speechly::slu::v1::SLUResponse, ::speechly::slu::v1::SLURequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestStream(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Stream : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_Stream() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc_impl::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this] { return this->Stream(); }));
    }
    ~ExperimentalWithRawCallbackMethod_Stream() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::speechly::slu::v1::SLUResponse, ::speechly::slu::v1::SLURequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::experimental::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* Stream() {
      return new ::grpc_impl::internal::UnimplementedBidiReactor<
        ::grpc::ByteBuffer, ::grpc::ByteBuffer>;}
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

}  // namespace v1
}  // namespace slu
}  // namespace speechly


#endif  // GRPC_speechly_2fslu_2fv1_2fslu_2eproto__INCLUDED
