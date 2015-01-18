// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Properties.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Properties.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* Properties_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Properties_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Properties_2eproto() {
  protobuf_AddDesc_Properties_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Properties.proto");
  GOOGLE_CHECK(file != NULL);
  Properties_descriptor_ = file->message_type(0);
  static const int Properties_offsets_[10] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, title_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, icon_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, width_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, useopengl_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, openglmajorversion_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, openglminorversion_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, flags_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, showcursor_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, scrollamount_),
  };
  Properties_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Properties_descriptor_,
      Properties::default_instance_,
      Properties_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Properties, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Properties));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Properties_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Properties_descriptor_, &Properties::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Properties_2eproto() {
  delete Properties::default_instance_;
  delete Properties_reflection_;
}

void protobuf_AddDesc_Properties_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020Properties.proto\"\361\001\n\nProperties\022\r\n\005tit"
    "le\030\001 \002(\t\022\014\n\004icon\030\002 \001(\t\022\023\n\005width\030\003 \002(\005:\0041"
    "280\022\023\n\006height\030\004 \002(\005:\003720\022\030\n\tuseOpenGL\030\005 "
    "\001(\010:\005false\022\035\n\022openGLMajorVersion\030\006 \001(\005:\001"
    "2\022\035\n\022openGLMinorVersion\030\007 \001(\005:\0011\022\020\n\005flag"
    "s\030\010 \001(\005:\0014\022\030\n\nshowCursor\030\t \001(\010:\004true\022\030\n\014"
    "scrollAmount\030\n \001(\005:\00210", 262);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Properties.proto", &protobuf_RegisterTypes);
  Properties::default_instance_ = new Properties();
  Properties::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Properties_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Properties_2eproto {
  StaticDescriptorInitializer_Properties_2eproto() {
    protobuf_AddDesc_Properties_2eproto();
  }
} static_descriptor_initializer_Properties_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Properties::kTitleFieldNumber;
const int Properties::kIconFieldNumber;
const int Properties::kWidthFieldNumber;
const int Properties::kHeightFieldNumber;
const int Properties::kUseOpenGLFieldNumber;
const int Properties::kOpenGLMajorVersionFieldNumber;
const int Properties::kOpenGLMinorVersionFieldNumber;
const int Properties::kFlagsFieldNumber;
const int Properties::kShowCursorFieldNumber;
const int Properties::kScrollAmountFieldNumber;
#endif  // !_MSC_VER

Properties::Properties()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Properties)
}

void Properties::InitAsDefaultInstance() {
}

Properties::Properties(const Properties& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Properties)
}

void Properties::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  title_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  icon_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  width_ = 1280;
  height_ = 720;
  useopengl_ = false;
  openglmajorversion_ = 2;
  openglminorversion_ = 1;
  flags_ = 4;
  showcursor_ = true;
  scrollamount_ = 10;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Properties::~Properties() {
  // @@protoc_insertion_point(destructor:Properties)
  SharedDtor();
}

void Properties::SharedDtor() {
  if (title_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete title_;
  }
  if (icon_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete icon_;
  }
  if (this != default_instance_) {
  }
}

void Properties::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Properties::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Properties_descriptor_;
}

const Properties& Properties::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Properties_2eproto();
  return *default_instance_;
}

Properties* Properties::default_instance_ = NULL;

Properties* Properties::New() const {
  return new Properties;
}

void Properties::Clear() {
  if (_has_bits_[0 / 32] & 255) {
    if (has_title()) {
      if (title_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        title_->clear();
      }
    }
    if (has_icon()) {
      if (icon_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        icon_->clear();
      }
    }
    width_ = 1280;
    height_ = 720;
    useopengl_ = false;
    openglmajorversion_ = 2;
    openglminorversion_ = 1;
    flags_ = 4;
  }
  if (_has_bits_[8 / 32] & 768) {
    showcursor_ = true;
    scrollamount_ = 10;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Properties::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Properties)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string title = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_title()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->title().data(), this->title().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "title");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_icon;
        break;
      }

      // optional string icon = 2;
      case 2: {
        if (tag == 18) {
         parse_icon:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_icon()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->icon().data(), this->icon().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "icon");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_width;
        break;
      }

      // required int32 width = 3 [default = 1280];
      case 3: {
        if (tag == 24) {
         parse_width:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &width_)));
          set_has_width();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_height;
        break;
      }

      // required int32 height = 4 [default = 720];
      case 4: {
        if (tag == 32) {
         parse_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &height_)));
          set_has_height();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_useOpenGL;
        break;
      }

      // optional bool useOpenGL = 5 [default = false];
      case 5: {
        if (tag == 40) {
         parse_useOpenGL:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &useopengl_)));
          set_has_useopengl();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_openGLMajorVersion;
        break;
      }

      // optional int32 openGLMajorVersion = 6 [default = 2];
      case 6: {
        if (tag == 48) {
         parse_openGLMajorVersion:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &openglmajorversion_)));
          set_has_openglmajorversion();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_openGLMinorVersion;
        break;
      }

      // optional int32 openGLMinorVersion = 7 [default = 1];
      case 7: {
        if (tag == 56) {
         parse_openGLMinorVersion:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &openglminorversion_)));
          set_has_openglminorversion();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_flags;
        break;
      }

      // optional int32 flags = 8 [default = 4];
      case 8: {
        if (tag == 64) {
         parse_flags:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &flags_)));
          set_has_flags();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(72)) goto parse_showCursor;
        break;
      }

      // optional bool showCursor = 9 [default = true];
      case 9: {
        if (tag == 72) {
         parse_showCursor:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &showcursor_)));
          set_has_showcursor();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(80)) goto parse_scrollAmount;
        break;
      }

      // optional int32 scrollAmount = 10 [default = 10];
      case 10: {
        if (tag == 80) {
         parse_scrollAmount:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &scrollamount_)));
          set_has_scrollamount();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Properties)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Properties)
  return false;
#undef DO_
}

void Properties::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Properties)
  // required string title = 1;
  if (has_title()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->title().data(), this->title().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "title");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->title(), output);
  }

  // optional string icon = 2;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "icon");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->icon(), output);
  }

  // required int32 width = 3 [default = 1280];
  if (has_width()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->width(), output);
  }

  // required int32 height = 4 [default = 720];
  if (has_height()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->height(), output);
  }

  // optional bool useOpenGL = 5 [default = false];
  if (has_useopengl()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(5, this->useopengl(), output);
  }

  // optional int32 openGLMajorVersion = 6 [default = 2];
  if (has_openglmajorversion()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->openglmajorversion(), output);
  }

  // optional int32 openGLMinorVersion = 7 [default = 1];
  if (has_openglminorversion()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->openglminorversion(), output);
  }

  // optional int32 flags = 8 [default = 4];
  if (has_flags()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->flags(), output);
  }

  // optional bool showCursor = 9 [default = true];
  if (has_showcursor()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(9, this->showcursor(), output);
  }

  // optional int32 scrollAmount = 10 [default = 10];
  if (has_scrollamount()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(10, this->scrollamount(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Properties)
}

::google::protobuf::uint8* Properties::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Properties)
  // required string title = 1;
  if (has_title()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->title().data(), this->title().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "title");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->title(), target);
  }

  // optional string icon = 2;
  if (has_icon()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->icon().data(), this->icon().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "icon");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->icon(), target);
  }

  // required int32 width = 3 [default = 1280];
  if (has_width()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->width(), target);
  }

  // required int32 height = 4 [default = 720];
  if (has_height()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->height(), target);
  }

  // optional bool useOpenGL = 5 [default = false];
  if (has_useopengl()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(5, this->useopengl(), target);
  }

  // optional int32 openGLMajorVersion = 6 [default = 2];
  if (has_openglmajorversion()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->openglmajorversion(), target);
  }

  // optional int32 openGLMinorVersion = 7 [default = 1];
  if (has_openglminorversion()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->openglminorversion(), target);
  }

  // optional int32 flags = 8 [default = 4];
  if (has_flags()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->flags(), target);
  }

  // optional bool showCursor = 9 [default = true];
  if (has_showcursor()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(9, this->showcursor(), target);
  }

  // optional int32 scrollAmount = 10 [default = 10];
  if (has_scrollamount()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(10, this->scrollamount(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Properties)
  return target;
}

int Properties::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string title = 1;
    if (has_title()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->title());
    }

    // optional string icon = 2;
    if (has_icon()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->icon());
    }

    // required int32 width = 3 [default = 1280];
    if (has_width()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->width());
    }

    // required int32 height = 4 [default = 720];
    if (has_height()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->height());
    }

    // optional bool useOpenGL = 5 [default = false];
    if (has_useopengl()) {
      total_size += 1 + 1;
    }

    // optional int32 openGLMajorVersion = 6 [default = 2];
    if (has_openglmajorversion()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->openglmajorversion());
    }

    // optional int32 openGLMinorVersion = 7 [default = 1];
    if (has_openglminorversion()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->openglminorversion());
    }

    // optional int32 flags = 8 [default = 4];
    if (has_flags()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->flags());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional bool showCursor = 9 [default = true];
    if (has_showcursor()) {
      total_size += 1 + 1;
    }

    // optional int32 scrollAmount = 10 [default = 10];
    if (has_scrollamount()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->scrollamount());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Properties::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Properties* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Properties*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Properties::MergeFrom(const Properties& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_title()) {
      set_title(from.title());
    }
    if (from.has_icon()) {
      set_icon(from.icon());
    }
    if (from.has_width()) {
      set_width(from.width());
    }
    if (from.has_height()) {
      set_height(from.height());
    }
    if (from.has_useopengl()) {
      set_useopengl(from.useopengl());
    }
    if (from.has_openglmajorversion()) {
      set_openglmajorversion(from.openglmajorversion());
    }
    if (from.has_openglminorversion()) {
      set_openglminorversion(from.openglminorversion());
    }
    if (from.has_flags()) {
      set_flags(from.flags());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_showcursor()) {
      set_showcursor(from.showcursor());
    }
    if (from.has_scrollamount()) {
      set_scrollamount(from.scrollamount());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Properties::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Properties::CopyFrom(const Properties& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Properties::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000d) != 0x0000000d) return false;

  return true;
}

void Properties::Swap(Properties* other) {
  if (other != this) {
    std::swap(title_, other->title_);
    std::swap(icon_, other->icon_);
    std::swap(width_, other->width_);
    std::swap(height_, other->height_);
    std::swap(useopengl_, other->useopengl_);
    std::swap(openglmajorversion_, other->openglmajorversion_);
    std::swap(openglminorversion_, other->openglminorversion_);
    std::swap(flags_, other->flags_);
    std::swap(showcursor_, other->showcursor_);
    std::swap(scrollamount_, other->scrollamount_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Properties::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Properties_descriptor_;
  metadata.reflection = Properties_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
