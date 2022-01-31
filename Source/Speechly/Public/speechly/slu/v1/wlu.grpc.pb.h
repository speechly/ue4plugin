// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: speechly/slu/v1/wlu.proto
#ifndef GRPC_speechly_2fslu_2fv1_2fwlu_2eproto__INCLUDED
#define GRPC_speechly_2fslu_2fv1_2fwlu_2eproto__INCLUDED

#include "speechly/slu/v1/wlu.pb.h"

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

// Service that implements Speechly WLU (Written Language Understanding).
//
// To use this service you MUST use an access token from Speechly Identity API.
// The token MUST be passed in gRPC metadata with `Authorization` key and `Bearer ACCESS_TOKEN` as value, e.g. in Go:
//
// ```
// ctx := context.Background()
// ctx = metadata.AppendToOutgoingContext(ctx, "Authorization", "Bearer "+accessToken)
// res, err := speechlyWLUClient.Text(ctx, req)
// ```
class WLU final {
 public:
  static constexpr char const* service_full_name() {
    return "speechly.slu.v1.WLU";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Performs recognition of a text with specified language.
    virtual ::grpc::Status Text(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::speechly::slu::v1::WLUResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::WLUResponse>> AsyncText(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::WLUResponse>>(AsyncTextRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::WLUResponse>> PrepareAsyncText(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::WLUResponse>>(PrepareAsyncTextRaw(context, request, cq));
    }
    // Performs recognition of a batch of texts with specified language.
    virtual ::grpc::Status Texts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::speechly::slu::v1::TextsResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::TextsResponse>> AsyncTexts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::TextsResponse>>(AsyncTextsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::TextsResponse>> PrepareAsyncTexts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::TextsResponse>>(PrepareAsyncTextsRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      // Performs recognition of a text with specified language.
      virtual void Text(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Text(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::WLUResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Text(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      virtual void Text(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::WLUResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      // Performs recognition of a batch of texts with specified language.
      virtual void Texts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Texts(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::TextsResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Texts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      virtual void Texts(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::TextsResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::WLUResponse>* AsyncTextRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::WLUResponse>* PrepareAsyncTextRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::TextsResponse>* AsyncTextsRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::speechly::slu::v1::TextsResponse>* PrepareAsyncTextsRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status Text(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::speechly::slu::v1::WLUResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::WLUResponse>> AsyncText(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::WLUResponse>>(AsyncTextRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::WLUResponse>> PrepareAsyncText(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::WLUResponse>>(PrepareAsyncTextRaw(context, request, cq));
    }
    ::grpc::Status Texts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::speechly::slu::v1::TextsResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::TextsResponse>> AsyncTexts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::TextsResponse>>(AsyncTextsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::TextsResponse>> PrepareAsyncTexts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::TextsResponse>>(PrepareAsyncTextsRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void Text(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response, std::function<void(::grpc::Status)>) override;
      void Text(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::WLUResponse* response, std::function<void(::grpc::Status)>) override;
      void Text(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      void Text(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::WLUResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      void Texts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response, std::function<void(::grpc::Status)>) override;
      void Texts(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::TextsResponse* response, std::function<void(::grpc::Status)>) override;
      void Texts(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      void Texts(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::speechly::slu::v1::TextsResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
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
    ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::WLUResponse>* AsyncTextRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::WLUResponse>* PrepareAsyncTextRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::WLURequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::TextsResponse>* AsyncTextsRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::speechly::slu::v1::TextsResponse>* PrepareAsyncTextsRaw(::grpc::ClientContext* context, const ::speechly::slu::v1::TextsRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Text_;
    const ::grpc::internal::RpcMethod rpcmethod_Texts_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Performs recognition of a text with specified language.
    virtual ::grpc::Status Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response);
    // Performs recognition of a batch of texts with specified language.
    virtual ::grpc::Status Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Text : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Text() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Text() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestText(::grpc::ServerContext* context, ::speechly::slu::v1::WLURequest* request, ::grpc::ServerAsyncResponseWriter< ::speechly::slu::v1::WLUResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Texts : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Texts() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_Texts() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestTexts(::grpc::ServerContext* context, ::speechly::slu::v1::TextsRequest* request, ::grpc::ServerAsyncResponseWriter< ::speechly::slu::v1::TextsResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Text<WithAsyncMethod_Texts<Service > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Text : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_Text() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::speechly::slu::v1::WLURequest, ::speechly::slu::v1::WLUResponse>(
          [this](::grpc::ServerContext* context,
                 const ::speechly::slu::v1::WLURequest* request,
                 ::speechly::slu::v1::WLUResponse* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->Text(context, request, response, controller);
                 }));
    }
    void SetMessageAllocatorFor_Text(
        ::grpc::experimental::MessageAllocator< ::speechly::slu::v1::WLURequest, ::speechly::slu::v1::WLUResponse>* allocator) {
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::speechly::slu::v1::WLURequest, ::speechly::slu::v1::WLUResponse>*>(
          ::grpc::Service::experimental().GetHandler(0))
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_Text() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Texts : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_Texts() {
      ::grpc::Service::experimental().MarkMethodCallback(1,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::speechly::slu::v1::TextsRequest, ::speechly::slu::v1::TextsResponse>(
          [this](::grpc::ServerContext* context,
                 const ::speechly::slu::v1::TextsRequest* request,
                 ::speechly::slu::v1::TextsResponse* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->Texts(context, request, response, controller);
                 }));
    }
    void SetMessageAllocatorFor_Texts(
        ::grpc::experimental::MessageAllocator< ::speechly::slu::v1::TextsRequest, ::speechly::slu::v1::TextsResponse>* allocator) {
      static_cast<::grpc_impl::internal::CallbackUnaryHandler< ::speechly::slu::v1::TextsRequest, ::speechly::slu::v1::TextsResponse>*>(
          ::grpc::Service::experimental().GetHandler(1))
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_Texts() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  typedef ExperimentalWithCallbackMethod_Text<ExperimentalWithCallbackMethod_Texts<Service > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Text : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Text() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Text() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Texts : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Texts() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_Texts() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Text : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_Text() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Text() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestText(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_Texts : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_Texts() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_Texts() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestTexts(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Text : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_Text() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->Text(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_Text() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void Text(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Texts : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_Texts() {
      ::grpc::Service::experimental().MarkMethodRawCallback(1,
        new ::grpc_impl::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->Texts(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_Texts() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void Texts(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Text : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Text() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::speechly::slu::v1::WLURequest, ::speechly::slu::v1::WLUResponse>(std::bind(&WithStreamedUnaryMethod_Text<BaseClass>::StreamedText, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Text() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Text(::grpc::ServerContext* context, const ::speechly::slu::v1::WLURequest* request, ::speechly::slu::v1::WLUResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedText(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::speechly::slu::v1::WLURequest,::speechly::slu::v1::WLUResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Texts : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Texts() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::speechly::slu::v1::TextsRequest, ::speechly::slu::v1::TextsResponse>(std::bind(&WithStreamedUnaryMethod_Texts<BaseClass>::StreamedTexts, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Texts() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Texts(::grpc::ServerContext* context, const ::speechly::slu::v1::TextsRequest* request, ::speechly::slu::v1::TextsResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedTexts(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::speechly::slu::v1::TextsRequest,::speechly::slu::v1::TextsResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Text<WithStreamedUnaryMethod_Texts<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Text<WithStreamedUnaryMethod_Texts<Service > > StreamedService;
};

}  // namespace v1
}  // namespace slu
}  // namespace speechly


#endif  // GRPC_speechly_2fslu_2fv1_2fwlu_2eproto__INCLUDED
