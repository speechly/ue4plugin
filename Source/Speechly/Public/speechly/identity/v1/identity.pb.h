// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: speechly/identity/v1/identity.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_speechly_2fidentity_2fv1_2fidentity_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_speechly_2fidentity_2fv1_2fidentity_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3008000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3008000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_speechly_2fidentity_2fv1_2fidentity_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_speechly_2fidentity_2fv1_2fidentity_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto;
namespace speechly {
namespace identity {
namespace v1 {
class LoginRequest;
class LoginRequestDefaultTypeInternal;
extern LoginRequestDefaultTypeInternal _LoginRequest_default_instance_;
class LoginResponse;
class LoginResponseDefaultTypeInternal;
extern LoginResponseDefaultTypeInternal _LoginResponse_default_instance_;
}  // namespace v1
}  // namespace identity
}  // namespace speechly
PROTOBUF_NAMESPACE_OPEN
template<> ::speechly::identity::v1::LoginRequest* Arena::CreateMaybeMessage<::speechly::identity::v1::LoginRequest>(Arena*);
template<> ::speechly::identity::v1::LoginResponse* Arena::CreateMaybeMessage<::speechly::identity::v1::LoginResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace speechly {
namespace identity {
namespace v1 {

// ===================================================================

class LoginRequest :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:speechly.identity.v1.LoginRequest) */ {
 public:
  LoginRequest();
  virtual ~LoginRequest();

  LoginRequest(const LoginRequest& from);
  LoginRequest(LoginRequest&& from) noexcept
    : LoginRequest() {
    *this = ::std::move(from);
  }

  inline LoginRequest& operator=(const LoginRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline LoginRequest& operator=(LoginRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const LoginRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const LoginRequest* internal_default_instance() {
    return reinterpret_cast<const LoginRequest*>(
               &_LoginRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(LoginRequest* other);
  friend void swap(LoginRequest& a, LoginRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline LoginRequest* New() const final {
    return CreateMaybeMessage<LoginRequest>(nullptr);
  }

  LoginRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<LoginRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const LoginRequest& from);
  void MergeFrom(const LoginRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(LoginRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "speechly.identity.v1.LoginRequest";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto);
    return ::descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string device_id = 1;
  void clear_device_id();
  static const int kDeviceIdFieldNumber = 1;
  const std::string& device_id() const;
  void set_device_id(const std::string& value);
  void set_device_id(std::string&& value);
  void set_device_id(const char* value);
  void set_device_id(const char* value, size_t size);
  std::string* mutable_device_id();
  std::string* release_device_id();
  void set_allocated_device_id(std::string* device_id);

  // string app_id = 2;
  void clear_app_id();
  static const int kAppIdFieldNumber = 2;
  const std::string& app_id() const;
  void set_app_id(const std::string& value);
  void set_app_id(std::string&& value);
  void set_app_id(const char* value);
  void set_app_id(const char* value, size_t size);
  std::string* mutable_app_id();
  std::string* release_app_id();
  void set_allocated_app_id(std::string* app_id);

  // string language_code = 3;
  void clear_language_code();
  static const int kLanguageCodeFieldNumber = 3;
  const std::string& language_code() const;
  void set_language_code(const std::string& value);
  void set_language_code(std::string&& value);
  void set_language_code(const char* value);
  void set_language_code(const char* value, size_t size);
  std::string* mutable_language_code();
  std::string* release_language_code();
  void set_allocated_language_code(std::string* language_code);

  // string config_id = 4;
  void clear_config_id();
  static const int kConfigIdFieldNumber = 4;
  const std::string& config_id() const;
  void set_config_id(const std::string& value);
  void set_config_id(std::string&& value);
  void set_config_id(const char* value);
  void set_config_id(const char* value, size_t size);
  std::string* mutable_config_id();
  std::string* release_config_id();
  void set_allocated_config_id(std::string* config_id);

  // @@protoc_insertion_point(class_scope:speechly.identity.v1.LoginRequest)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr device_id_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr app_id_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr language_code_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr config_id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_speechly_2fidentity_2fv1_2fidentity_2eproto;
};
// -------------------------------------------------------------------

class LoginResponse :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:speechly.identity.v1.LoginResponse) */ {
 public:
  LoginResponse();
  virtual ~LoginResponse();

  LoginResponse(const LoginResponse& from);
  LoginResponse(LoginResponse&& from) noexcept
    : LoginResponse() {
    *this = ::std::move(from);
  }

  inline LoginResponse& operator=(const LoginResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline LoginResponse& operator=(LoginResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const LoginResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const LoginResponse* internal_default_instance() {
    return reinterpret_cast<const LoginResponse*>(
               &_LoginResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(LoginResponse* other);
  friend void swap(LoginResponse& a, LoginResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline LoginResponse* New() const final {
    return CreateMaybeMessage<LoginResponse>(nullptr);
  }

  LoginResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<LoginResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const LoginResponse& from);
  void MergeFrom(const LoginResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(LoginResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "speechly.identity.v1.LoginResponse";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto);
    return ::descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string token = 1;
  void clear_token();
  static const int kTokenFieldNumber = 1;
  const std::string& token() const;
  void set_token(const std::string& value);
  void set_token(std::string&& value);
  void set_token(const char* value);
  void set_token(const char* value, size_t size);
  std::string* mutable_token();
  std::string* release_token();
  void set_allocated_token(std::string* token);

  // @@protoc_insertion_point(class_scope:speechly.identity.v1.LoginResponse)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr token_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_speechly_2fidentity_2fv1_2fidentity_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LoginRequest

// string device_id = 1;
inline void LoginRequest::clear_device_id() {
  device_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& LoginRequest::device_id() const {
  // @@protoc_insertion_point(field_get:speechly.identity.v1.LoginRequest.device_id)
  return device_id_.GetNoArena();
}
inline void LoginRequest::set_device_id(const std::string& value) {
  
  device_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:speechly.identity.v1.LoginRequest.device_id)
}
inline void LoginRequest::set_device_id(std::string&& value) {
  
  device_id_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:speechly.identity.v1.LoginRequest.device_id)
}
inline void LoginRequest::set_device_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  device_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:speechly.identity.v1.LoginRequest.device_id)
}
inline void LoginRequest::set_device_id(const char* value, size_t size) {
  
  device_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:speechly.identity.v1.LoginRequest.device_id)
}
inline std::string* LoginRequest::mutable_device_id() {
  
  // @@protoc_insertion_point(field_mutable:speechly.identity.v1.LoginRequest.device_id)
  return device_id_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* LoginRequest::release_device_id() {
  // @@protoc_insertion_point(field_release:speechly.identity.v1.LoginRequest.device_id)
  
  return device_id_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void LoginRequest::set_allocated_device_id(std::string* device_id) {
  if (device_id != nullptr) {
    
  } else {
    
  }
  device_id_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), device_id);
  // @@protoc_insertion_point(field_set_allocated:speechly.identity.v1.LoginRequest.device_id)
}

// string app_id = 2;
inline void LoginRequest::clear_app_id() {
  app_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& LoginRequest::app_id() const {
  // @@protoc_insertion_point(field_get:speechly.identity.v1.LoginRequest.app_id)
  return app_id_.GetNoArena();
}
inline void LoginRequest::set_app_id(const std::string& value) {
  
  app_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:speechly.identity.v1.LoginRequest.app_id)
}
inline void LoginRequest::set_app_id(std::string&& value) {
  
  app_id_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:speechly.identity.v1.LoginRequest.app_id)
}
inline void LoginRequest::set_app_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  app_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:speechly.identity.v1.LoginRequest.app_id)
}
inline void LoginRequest::set_app_id(const char* value, size_t size) {
  
  app_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:speechly.identity.v1.LoginRequest.app_id)
}
inline std::string* LoginRequest::mutable_app_id() {
  
  // @@protoc_insertion_point(field_mutable:speechly.identity.v1.LoginRequest.app_id)
  return app_id_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* LoginRequest::release_app_id() {
  // @@protoc_insertion_point(field_release:speechly.identity.v1.LoginRequest.app_id)
  
  return app_id_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void LoginRequest::set_allocated_app_id(std::string* app_id) {
  if (app_id != nullptr) {
    
  } else {
    
  }
  app_id_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), app_id);
  // @@protoc_insertion_point(field_set_allocated:speechly.identity.v1.LoginRequest.app_id)
}

// string language_code = 3;
inline void LoginRequest::clear_language_code() {
  language_code_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& LoginRequest::language_code() const {
  // @@protoc_insertion_point(field_get:speechly.identity.v1.LoginRequest.language_code)
  return language_code_.GetNoArena();
}
inline void LoginRequest::set_language_code(const std::string& value) {
  
  language_code_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:speechly.identity.v1.LoginRequest.language_code)
}
inline void LoginRequest::set_language_code(std::string&& value) {
  
  language_code_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:speechly.identity.v1.LoginRequest.language_code)
}
inline void LoginRequest::set_language_code(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  language_code_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:speechly.identity.v1.LoginRequest.language_code)
}
inline void LoginRequest::set_language_code(const char* value, size_t size) {
  
  language_code_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:speechly.identity.v1.LoginRequest.language_code)
}
inline std::string* LoginRequest::mutable_language_code() {
  
  // @@protoc_insertion_point(field_mutable:speechly.identity.v1.LoginRequest.language_code)
  return language_code_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* LoginRequest::release_language_code() {
  // @@protoc_insertion_point(field_release:speechly.identity.v1.LoginRequest.language_code)
  
  return language_code_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void LoginRequest::set_allocated_language_code(std::string* language_code) {
  if (language_code != nullptr) {
    
  } else {
    
  }
  language_code_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), language_code);
  // @@protoc_insertion_point(field_set_allocated:speechly.identity.v1.LoginRequest.language_code)
}

// string config_id = 4;
inline void LoginRequest::clear_config_id() {
  config_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& LoginRequest::config_id() const {
  // @@protoc_insertion_point(field_get:speechly.identity.v1.LoginRequest.config_id)
  return config_id_.GetNoArena();
}
inline void LoginRequest::set_config_id(const std::string& value) {
  
  config_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:speechly.identity.v1.LoginRequest.config_id)
}
inline void LoginRequest::set_config_id(std::string&& value) {
  
  config_id_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:speechly.identity.v1.LoginRequest.config_id)
}
inline void LoginRequest::set_config_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  config_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:speechly.identity.v1.LoginRequest.config_id)
}
inline void LoginRequest::set_config_id(const char* value, size_t size) {
  
  config_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:speechly.identity.v1.LoginRequest.config_id)
}
inline std::string* LoginRequest::mutable_config_id() {
  
  // @@protoc_insertion_point(field_mutable:speechly.identity.v1.LoginRequest.config_id)
  return config_id_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* LoginRequest::release_config_id() {
  // @@protoc_insertion_point(field_release:speechly.identity.v1.LoginRequest.config_id)
  
  return config_id_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void LoginRequest::set_allocated_config_id(std::string* config_id) {
  if (config_id != nullptr) {
    
  } else {
    
  }
  config_id_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), config_id);
  // @@protoc_insertion_point(field_set_allocated:speechly.identity.v1.LoginRequest.config_id)
}

// -------------------------------------------------------------------

// LoginResponse

// string token = 1;
inline void LoginResponse::clear_token() {
  token_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& LoginResponse::token() const {
  // @@protoc_insertion_point(field_get:speechly.identity.v1.LoginResponse.token)
  return token_.GetNoArena();
}
inline void LoginResponse::set_token(const std::string& value) {
  
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:speechly.identity.v1.LoginResponse.token)
}
inline void LoginResponse::set_token(std::string&& value) {
  
  token_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:speechly.identity.v1.LoginResponse.token)
}
inline void LoginResponse::set_token(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:speechly.identity.v1.LoginResponse.token)
}
inline void LoginResponse::set_token(const char* value, size_t size) {
  
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:speechly.identity.v1.LoginResponse.token)
}
inline std::string* LoginResponse::mutable_token() {
  
  // @@protoc_insertion_point(field_mutable:speechly.identity.v1.LoginResponse.token)
  return token_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* LoginResponse::release_token() {
  // @@protoc_insertion_point(field_release:speechly.identity.v1.LoginResponse.token)
  
  return token_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void LoginResponse::set_allocated_token(std::string* token) {
  if (token != nullptr) {
    
  } else {
    
  }
  token_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), token);
  // @@protoc_insertion_point(field_set_allocated:speechly.identity.v1.LoginResponse.token)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace v1
}  // namespace identity
}  // namespace speechly

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_speechly_2fidentity_2fv1_2fidentity_2eproto