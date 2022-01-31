// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: speechly/identity/v1/identity.proto

#include "IncludeBegin.h"

#include "speechly/identity/v1/identity.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace speechly {
namespace identity {
namespace v1 {
class LoginRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<LoginRequest> _instance;
} _LoginRequest_default_instance_;
class LoginResponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<LoginResponse> _instance;
} _LoginResponse_default_instance_;
}  // namespace v1
}  // namespace identity
}  // namespace speechly
static void InitDefaultsscc_info_LoginRequest_speechly_2fidentity_2fv1_2fidentity_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::speechly::identity::v1::_LoginRequest_default_instance_;
    new (ptr) ::speechly::identity::v1::LoginRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::speechly::identity::v1::LoginRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_LoginRequest_speechly_2fidentity_2fv1_2fidentity_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_LoginRequest_speechly_2fidentity_2fv1_2fidentity_2eproto}, {}};

static void InitDefaultsscc_info_LoginResponse_speechly_2fidentity_2fv1_2fidentity_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::speechly::identity::v1::_LoginResponse_default_instance_;
    new (ptr) ::speechly::identity::v1::LoginResponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::speechly::identity::v1::LoginResponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_LoginResponse_speechly_2fidentity_2fv1_2fidentity_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_LoginResponse_speechly_2fidentity_2fv1_2fidentity_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_speechly_2fidentity_2fv1_2fidentity_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_speechly_2fidentity_2fv1_2fidentity_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_speechly_2fidentity_2fv1_2fidentity_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_speechly_2fidentity_2fv1_2fidentity_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::speechly::identity::v1::LoginRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::speechly::identity::v1::LoginRequest, device_id_),
  PROTOBUF_FIELD_OFFSET(::speechly::identity::v1::LoginRequest, app_id_),
  PROTOBUF_FIELD_OFFSET(::speechly::identity::v1::LoginRequest, language_code_),
  PROTOBUF_FIELD_OFFSET(::speechly::identity::v1::LoginRequest, config_id_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::speechly::identity::v1::LoginResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::speechly::identity::v1::LoginResponse, token_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::speechly::identity::v1::LoginRequest)},
  { 9, -1, sizeof(::speechly::identity::v1::LoginResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::speechly::identity::v1::_LoginRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::speechly::identity::v1::_LoginResponse_default_instance_),
};

const char descriptor_table_protodef_speechly_2fidentity_2fv1_2fidentity_2eproto[] =
  "\n#speechly/identity/v1/identity.proto\022\024s"
  "peechly.identity.v1\"[\n\014LoginRequest\022\021\n\td"
  "evice_id\030\001 \001(\t\022\016\n\006app_id\030\002 \001(\t\022\025\n\rlangua"
  "ge_code\030\003 \001(\t\022\021\n\tconfig_id\030\004 \001(\t\"\036\n\rLogi"
  "nResponse\022\r\n\005token\030\001 \001(\t2\\\n\010Identity\022P\n\005"
  "Login\022\".speechly.identity.v1.LoginReques"
  "t\032#.speechly.identity.v1.LoginResponseB\200"
  "\001\n\030com.speechly.identity.v1B\rIdentityPro"
  "toP\001Z\037speechly/identity/v1;identityv1\242\002\003"
  "SIX\252\002\024Speechly.Identity.V1\312\002\024Speechly\\Id"
  "entity\\V1b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_sccs[2] = {
  &scc_info_LoginRequest_speechly_2fidentity_2fv1_2fidentity_2eproto.base,
  &scc_info_LoginResponse_speechly_2fidentity_2fv1_2fidentity_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_once;
static bool descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto = {
  &descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_initialized, descriptor_table_protodef_speechly_2fidentity_2fv1_2fidentity_2eproto, "speechly/identity/v1/identity.proto", 417,
  &descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_once, descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_sccs, descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_speechly_2fidentity_2fv1_2fidentity_2eproto::offsets,
  file_level_metadata_speechly_2fidentity_2fv1_2fidentity_2eproto, 2, file_level_enum_descriptors_speechly_2fidentity_2fv1_2fidentity_2eproto, file_level_service_descriptors_speechly_2fidentity_2fv1_2fidentity_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_speechly_2fidentity_2fv1_2fidentity_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_speechly_2fidentity_2fv1_2fidentity_2eproto), true);
namespace speechly {
namespace identity {
namespace v1 {

// ===================================================================

void LoginRequest::InitAsDefaultInstance() {
}
class LoginRequest::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int LoginRequest::kDeviceIdFieldNumber;
const int LoginRequest::kAppIdFieldNumber;
const int LoginRequest::kLanguageCodeFieldNumber;
const int LoginRequest::kConfigIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

LoginRequest::LoginRequest()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:speechly.identity.v1.LoginRequest)
}
LoginRequest::LoginRequest(const LoginRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  device_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.device_id().size() > 0) {
    device_id_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.device_id_);
  }
  app_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.app_id().size() > 0) {
    app_id_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.app_id_);
  }
  language_code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.language_code().size() > 0) {
    language_code_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.language_code_);
  }
  config_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.config_id().size() > 0) {
    config_id_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.config_id_);
  }
  // @@protoc_insertion_point(copy_constructor:speechly.identity.v1.LoginRequest)
}

void LoginRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_LoginRequest_speechly_2fidentity_2fv1_2fidentity_2eproto.base);
  device_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  app_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  language_code_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  config_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

LoginRequest::~LoginRequest() {
  // @@protoc_insertion_point(destructor:speechly.identity.v1.LoginRequest)
  SharedDtor();
}

void LoginRequest::SharedDtor() {
  device_id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  app_id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  language_code_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  config_id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void LoginRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const LoginRequest& LoginRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_LoginRequest_speechly_2fidentity_2fv1_2fidentity_2eproto.base);
  return *internal_default_instance();
}


void LoginRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:speechly.identity.v1.LoginRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  device_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  app_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  language_code_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  config_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* LoginRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string device_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_device_id(), ptr, ctx, "speechly.identity.v1.LoginRequest.device_id");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string app_id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_app_id(), ptr, ctx, "speechly.identity.v1.LoginRequest.app_id");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string language_code = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_language_code(), ptr, ctx, "speechly.identity.v1.LoginRequest.language_code");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string config_id = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_config_id(), ptr, ctx, "speechly.identity.v1.LoginRequest.config_id");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool LoginRequest::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:speechly.identity.v1.LoginRequest)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string device_id = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_device_id()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->device_id().data(), static_cast<int>(this->device_id().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "speechly.identity.v1.LoginRequest.device_id"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string app_id = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (18 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_app_id()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->app_id().data(), static_cast<int>(this->app_id().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "speechly.identity.v1.LoginRequest.app_id"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string language_code = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (26 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_language_code()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->language_code().data(), static_cast<int>(this->language_code().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "speechly.identity.v1.LoginRequest.language_code"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string config_id = 4;
      case 4: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (34 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_config_id()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->config_id().data(), static_cast<int>(this->config_id().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "speechly.identity.v1.LoginRequest.config_id"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:speechly.identity.v1.LoginRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:speechly.identity.v1.LoginRequest)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void LoginRequest::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:speechly.identity.v1.LoginRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string device_id = 1;
  if (this->device_id().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->device_id().data(), static_cast<int>(this->device_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.device_id");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->device_id(), output);
  }

  // string app_id = 2;
  if (this->app_id().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->app_id().data(), static_cast<int>(this->app_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.app_id");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->app_id(), output);
  }

  // string language_code = 3;
  if (this->language_code().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->language_code().data(), static_cast<int>(this->language_code().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.language_code");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->language_code(), output);
  }

  // string config_id = 4;
  if (this->config_id().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->config_id().data(), static_cast<int>(this->config_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.config_id");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->config_id(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:speechly.identity.v1.LoginRequest)
}

::PROTOBUF_NAMESPACE_ID::uint8* LoginRequest::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:speechly.identity.v1.LoginRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string device_id = 1;
  if (this->device_id().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->device_id().data(), static_cast<int>(this->device_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.device_id");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        1, this->device_id(), target);
  }

  // string app_id = 2;
  if (this->app_id().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->app_id().data(), static_cast<int>(this->app_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.app_id");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        2, this->app_id(), target);
  }

  // string language_code = 3;
  if (this->language_code().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->language_code().data(), static_cast<int>(this->language_code().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.language_code");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        3, this->language_code(), target);
  }

  // string config_id = 4;
  if (this->config_id().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->config_id().data(), static_cast<int>(this->config_id().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginRequest.config_id");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        4, this->config_id(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:speechly.identity.v1.LoginRequest)
  return target;
}

size_t LoginRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:speechly.identity.v1.LoginRequest)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string device_id = 1;
  if (this->device_id().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->device_id());
  }

  // string app_id = 2;
  if (this->app_id().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->app_id());
  }

  // string language_code = 3;
  if (this->language_code().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->language_code());
  }

  // string config_id = 4;
  if (this->config_id().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->config_id());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void LoginRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:speechly.identity.v1.LoginRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const LoginRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<LoginRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:speechly.identity.v1.LoginRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:speechly.identity.v1.LoginRequest)
    MergeFrom(*source);
  }
}

void LoginRequest::MergeFrom(const LoginRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:speechly.identity.v1.LoginRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.device_id().size() > 0) {

    device_id_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.device_id_);
  }
  if (from.app_id().size() > 0) {

    app_id_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.app_id_);
  }
  if (from.language_code().size() > 0) {

    language_code_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.language_code_);
  }
  if (from.config_id().size() > 0) {

    config_id_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.config_id_);
  }
}

void LoginRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:speechly.identity.v1.LoginRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LoginRequest::CopyFrom(const LoginRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:speechly.identity.v1.LoginRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LoginRequest::IsInitialized() const {
  return true;
}

void LoginRequest::Swap(LoginRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void LoginRequest::InternalSwap(LoginRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  device_id_.Swap(&other->device_id_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  app_id_.Swap(&other->app_id_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  language_code_.Swap(&other->language_code_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  config_id_.Swap(&other->config_id_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata LoginRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void LoginResponse::InitAsDefaultInstance() {
}
class LoginResponse::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int LoginResponse::kTokenFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

LoginResponse::LoginResponse()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:speechly.identity.v1.LoginResponse)
}
LoginResponse::LoginResponse(const LoginResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  token_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.token().size() > 0) {
    token_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.token_);
  }
  // @@protoc_insertion_point(copy_constructor:speechly.identity.v1.LoginResponse)
}

void LoginResponse::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_LoginResponse_speechly_2fidentity_2fv1_2fidentity_2eproto.base);
  token_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

LoginResponse::~LoginResponse() {
  // @@protoc_insertion_point(destructor:speechly.identity.v1.LoginResponse)
  SharedDtor();
}

void LoginResponse::SharedDtor() {
  token_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void LoginResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const LoginResponse& LoginResponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_LoginResponse_speechly_2fidentity_2fv1_2fidentity_2eproto.base);
  return *internal_default_instance();
}


void LoginResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:speechly.identity.v1.LoginResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  token_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* LoginResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string token = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_token(), ptr, ctx, "speechly.identity.v1.LoginResponse.token");
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool LoginResponse::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:speechly.identity.v1.LoginResponse)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string token = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_token()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->token().data(), static_cast<int>(this->token().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "speechly.identity.v1.LoginResponse.token"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:speechly.identity.v1.LoginResponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:speechly.identity.v1.LoginResponse)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void LoginResponse::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:speechly.identity.v1.LoginResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string token = 1;
  if (this->token().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->token().data(), static_cast<int>(this->token().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginResponse.token");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->token(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:speechly.identity.v1.LoginResponse)
}

::PROTOBUF_NAMESPACE_ID::uint8* LoginResponse::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:speechly.identity.v1.LoginResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string token = 1;
  if (this->token().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->token().data(), static_cast<int>(this->token().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "speechly.identity.v1.LoginResponse.token");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        1, this->token(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:speechly.identity.v1.LoginResponse)
  return target;
}

size_t LoginResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:speechly.identity.v1.LoginResponse)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string token = 1;
  if (this->token().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->token());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void LoginResponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:speechly.identity.v1.LoginResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const LoginResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<LoginResponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:speechly.identity.v1.LoginResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:speechly.identity.v1.LoginResponse)
    MergeFrom(*source);
  }
}

void LoginResponse::MergeFrom(const LoginResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:speechly.identity.v1.LoginResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.token().size() > 0) {

    token_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.token_);
  }
}

void LoginResponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:speechly.identity.v1.LoginResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LoginResponse::CopyFrom(const LoginResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:speechly.identity.v1.LoginResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LoginResponse::IsInitialized() const {
  return true;
}

void LoginResponse::Swap(LoginResponse* other) {
  if (other == this) return;
  InternalSwap(other);
}
void LoginResponse::InternalSwap(LoginResponse* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  token_.Swap(&other->token_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata LoginResponse::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace v1
}  // namespace identity
}  // namespace speechly
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::speechly::identity::v1::LoginRequest* Arena::CreateMaybeMessage< ::speechly::identity::v1::LoginRequest >(Arena* arena) {
  return Arena::CreateInternal< ::speechly::identity::v1::LoginRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::speechly::identity::v1::LoginResponse* Arena::CreateMaybeMessage< ::speechly::identity::v1::LoginResponse >(Arena* arena) {
  return Arena::CreateInternal< ::speechly::identity::v1::LoginResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>

#include "IncludeEnd.h"
