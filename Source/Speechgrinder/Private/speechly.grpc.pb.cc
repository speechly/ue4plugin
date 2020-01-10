// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: speechly.proto

#include "IncludeBegin.h"

#include "speechly.pb.h"
#include "speechly.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace v1 {

static const char* SLU_method_names[] = {
  "/v1.SLU/Stream",
};

std::unique_ptr< SLU::Stub> SLU::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< SLU::Stub> stub(new SLU::Stub(channel));
  return stub;
}

SLU::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Stream_(SLU_method_names[0], ::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::v1::SLURequest, ::v1::SLUResponse>* SLU::Stub::StreamRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::v1::SLURequest, ::v1::SLUResponse>::Create(channel_.get(), rpcmethod_Stream_, context);
}

::grpc::ClientAsyncReaderWriter< ::v1::SLURequest, ::v1::SLUResponse>* SLU::Stub::AsyncStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::v1::SLURequest, ::v1::SLUResponse>::Create(channel_.get(), cq, rpcmethod_Stream_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::v1::SLURequest, ::v1::SLUResponse>* SLU::Stub::PrepareAsyncStreamRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::v1::SLURequest, ::v1::SLUResponse>::Create(channel_.get(), cq, rpcmethod_Stream_, context, false, nullptr);
}

SLU::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SLU_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< SLU::Service, ::v1::SLURequest, ::v1::SLUResponse>(
          std::mem_fn(&SLU::Service::Stream), this)));
}

SLU::Service::~Service() {
}

::grpc::Status SLU::Service::Stream(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::v1::SLUResponse, ::v1::SLURequest>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* WLU_method_names[] = {
  "/v1.WLU/Text",
};

std::unique_ptr< WLU::Stub> WLU::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< WLU::Stub> stub(new WLU::Stub(channel));
  return stub;
}

WLU::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Text_(WLU_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status WLU::Stub::Text(::grpc::ClientContext* context, const ::v1::WLURequest& request, ::v1::WLUResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Text_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::v1::WLUResponse>* WLU::Stub::AsyncTextRaw(::grpc::ClientContext* context, const ::v1::WLURequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::v1::WLUResponse>::Create(channel_.get(), cq, rpcmethod_Text_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::v1::WLUResponse>* WLU::Stub::PrepareAsyncTextRaw(::grpc::ClientContext* context, const ::v1::WLURequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::v1::WLUResponse>::Create(channel_.get(), cq, rpcmethod_Text_, context, request, false);
}

WLU::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      WLU_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< WLU::Service, ::v1::WLURequest, ::v1::WLUResponse>(
          std::mem_fn(&WLU::Service::Text), this)));
}

WLU::Service::~Service() {
}

::grpc::Status WLU::Service::Text(::grpc::ServerContext* context, const ::v1::WLURequest* request, ::v1::WLUResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* Identity_method_names[] = {
  "/v1.Identity/Login",
};

std::unique_ptr< Identity::Stub> Identity::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Identity::Stub> stub(new Identity::Stub(channel));
  return stub;
}

Identity::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Login_(Identity_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Identity::Stub::Login(::grpc::ClientContext* context, const ::v1::LoginRequest& request, ::v1::LoginResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Login_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::v1::LoginResponse>* Identity::Stub::AsyncLoginRaw(::grpc::ClientContext* context, const ::v1::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::v1::LoginResponse>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::v1::LoginResponse>* Identity::Stub::PrepareAsyncLoginRaw(::grpc::ClientContext* context, const ::v1::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::v1::LoginResponse>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, false);
}

Identity::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Identity_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Identity::Service, ::v1::LoginRequest, ::v1::LoginResponse>(
          std::mem_fn(&Identity::Service::Login), this)));
}

Identity::Service::~Service() {
}

::grpc::Status Identity::Service::Login(::grpc::ServerContext* context, const ::v1::LoginRequest* request, ::v1::LoginResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace v1


#include "IncludeEnd.h"