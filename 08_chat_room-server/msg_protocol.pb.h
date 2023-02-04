// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_protocol.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_msg_5fprotocol_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_msg_5fprotocol_2eproto
#define PROTOBUF_USE_DLLS // 需要手动定义！
#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_msg_5fprotocol_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_msg_5fprotocol_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_msg_5fprotocol_2eproto;
namespace msg_protocol_pb {
class chat_publice;
struct chat_publiceDefaultTypeInternal;
extern chat_publiceDefaultTypeInternal _chat_publice_default_instance_;
class server_reply;
struct server_replyDefaultTypeInternal;
extern server_replyDefaultTypeInternal _server_reply_default_instance_;
class set_user_name;
struct set_user_nameDefaultTypeInternal;
extern set_user_nameDefaultTypeInternal _set_user_name_default_instance_;
}  // namespace msg_protocol_pb
PROTOBUF_NAMESPACE_OPEN
template<> ::msg_protocol_pb::chat_publice* Arena::CreateMaybeMessage<::msg_protocol_pb::chat_publice>(Arena*);
template<> ::msg_protocol_pb::server_reply* Arena::CreateMaybeMessage<::msg_protocol_pb::server_reply>(Arena*);
template<> ::msg_protocol_pb::set_user_name* Arena::CreateMaybeMessage<::msg_protocol_pb::set_user_name>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace msg_protocol_pb {

// ===================================================================

class set_user_name final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:msg_protocol_pb.set_user_name) */ {
 public:
  inline set_user_name() : set_user_name(nullptr) {}
  ~set_user_name() override;
  explicit PROTOBUF_CONSTEXPR set_user_name(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  set_user_name(const set_user_name& from);
  set_user_name(set_user_name&& from) noexcept
    : set_user_name() {
    *this = ::std::move(from);
  }

  inline set_user_name& operator=(const set_user_name& from) {
    CopyFrom(from);
    return *this;
  }
  inline set_user_name& operator=(set_user_name&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const set_user_name& default_instance() {
    return *internal_default_instance();
  }
  static inline const set_user_name* internal_default_instance() {
    return reinterpret_cast<const set_user_name*>(
               &_set_user_name_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(set_user_name& a, set_user_name& b) {
    a.Swap(&b);
  }
  inline void Swap(set_user_name* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(set_user_name* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  set_user_name* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<set_user_name>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const set_user_name& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const set_user_name& from) {
    set_user_name::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(set_user_name* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "msg_protocol_pb.set_user_name";
  }
  protected:
  explicit set_user_name(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
  };
  // string name = 1;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // @@protoc_insertion_point(class_scope:msg_protocol_pb.set_user_name)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_msg_5fprotocol_2eproto;
};
// -------------------------------------------------------------------

class chat_publice final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:msg_protocol_pb.chat_publice) */ {
 public:
  inline chat_publice() : chat_publice(nullptr) {}
  ~chat_publice() override;
  explicit PROTOBUF_CONSTEXPR chat_publice(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  chat_publice(const chat_publice& from);
  chat_publice(chat_publice&& from) noexcept
    : chat_publice() {
    *this = ::std::move(from);
  }

  inline chat_publice& operator=(const chat_publice& from) {
    CopyFrom(from);
    return *this;
  }
  inline chat_publice& operator=(chat_publice&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const chat_publice& default_instance() {
    return *internal_default_instance();
  }
  static inline const chat_publice* internal_default_instance() {
    return reinterpret_cast<const chat_publice*>(
               &_chat_publice_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(chat_publice& a, chat_publice& b) {
    a.Swap(&b);
  }
  inline void Swap(chat_publice* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(chat_publice* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  chat_publice* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<chat_publice>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const chat_publice& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const chat_publice& from) {
    chat_publice::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(chat_publice* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "msg_protocol_pb.chat_publice";
  }
  protected:
  explicit chat_publice(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 1,
  };
  // string msg = 1;
  void clear_msg();
  const std::string& msg() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_msg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_msg();
  PROTOBUF_NODISCARD std::string* release_msg();
  void set_allocated_msg(std::string* msg);
  private:
  const std::string& _internal_msg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_msg(const std::string& value);
  std::string* _internal_mutable_msg();
  public:

  // @@protoc_insertion_point(class_scope:msg_protocol_pb.chat_publice)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_msg_5fprotocol_2eproto;
};
// -------------------------------------------------------------------

class server_reply final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:msg_protocol_pb.server_reply) */ {
 public:
  inline server_reply() : server_reply(nullptr) {}
  ~server_reply() override;
  explicit PROTOBUF_CONSTEXPR server_reply(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  server_reply(const server_reply& from);
  server_reply(server_reply&& from) noexcept
    : server_reply() {
    *this = ::std::move(from);
  }

  inline server_reply& operator=(const server_reply& from) {
    CopyFrom(from);
    return *this;
  }
  inline server_reply& operator=(server_reply&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const server_reply& default_instance() {
    return *internal_default_instance();
  }
  static inline const server_reply* internal_default_instance() {
    return reinterpret_cast<const server_reply*>(
               &_server_reply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(server_reply& a, server_reply& b) {
    a.Swap(&b);
  }
  inline void Swap(server_reply* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(server_reply* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  server_reply* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<server_reply>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const server_reply& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const server_reply& from) {
    server_reply::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(server_reply* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "msg_protocol_pb.server_reply";
  }
  protected:
  explicit server_reply(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kUserNameFieldNumber = 1,
    kInfoFieldNumber = 2,
  };
  // string user_name = 1;
  void clear_user_name();
  const std::string& user_name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_user_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_user_name();
  PROTOBUF_NODISCARD std::string* release_user_name();
  void set_allocated_user_name(std::string* user_name);
  private:
  const std::string& _internal_user_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_user_name(const std::string& value);
  std::string* _internal_mutable_user_name();
  public:

  // string info = 2;
  void clear_info();
  const std::string& info() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_info(ArgT0&& arg0, ArgT... args);
  std::string* mutable_info();
  PROTOBUF_NODISCARD std::string* release_info();
  void set_allocated_info(std::string* info);
  private:
  const std::string& _internal_info() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_info(const std::string& value);
  std::string* _internal_mutable_info();
  public:

  // @@protoc_insertion_point(class_scope:msg_protocol_pb.server_reply)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr user_name_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr info_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_msg_5fprotocol_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// set_user_name

// string name = 1;
inline void set_user_name::clear_name() {
  _impl_.name_.ClearToEmpty();
}
inline const std::string& set_user_name::name() const {
  // @@protoc_insertion_point(field_get:msg_protocol_pb.set_user_name.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void set_user_name::set_name(ArgT0&& arg0, ArgT... args) {
 
 _impl_.name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg_protocol_pb.set_user_name.name)
}
inline std::string* set_user_name::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:msg_protocol_pb.set_user_name.name)
  return _s;
}
inline const std::string& set_user_name::_internal_name() const {
  return _impl_.name_.Get();
}
inline void set_user_name::_internal_set_name(const std::string& value) {
  
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* set_user_name::_internal_mutable_name() {
  
  return _impl_.name_.Mutable(GetArenaForAllocation());
}
inline std::string* set_user_name::release_name() {
  // @@protoc_insertion_point(field_release:msg_protocol_pb.set_user_name.name)
  return _impl_.name_.Release();
}
inline void set_user_name::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  _impl_.name_.SetAllocated(name, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg_protocol_pb.set_user_name.name)
}

// -------------------------------------------------------------------

// chat_publice

// string msg = 1;
inline void chat_publice::clear_msg() {
  _impl_.msg_.ClearToEmpty();
}
inline const std::string& chat_publice::msg() const {
  // @@protoc_insertion_point(field_get:msg_protocol_pb.chat_publice.msg)
  return _internal_msg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void chat_publice::set_msg(ArgT0&& arg0, ArgT... args) {
 
 _impl_.msg_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg_protocol_pb.chat_publice.msg)
}
inline std::string* chat_publice::mutable_msg() {
  std::string* _s = _internal_mutable_msg();
  // @@protoc_insertion_point(field_mutable:msg_protocol_pb.chat_publice.msg)
  return _s;
}
inline const std::string& chat_publice::_internal_msg() const {
  return _impl_.msg_.Get();
}
inline void chat_publice::_internal_set_msg(const std::string& value) {
  
  _impl_.msg_.Set(value, GetArenaForAllocation());
}
inline std::string* chat_publice::_internal_mutable_msg() {
  
  return _impl_.msg_.Mutable(GetArenaForAllocation());
}
inline std::string* chat_publice::release_msg() {
  // @@protoc_insertion_point(field_release:msg_protocol_pb.chat_publice.msg)
  return _impl_.msg_.Release();
}
inline void chat_publice::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  _impl_.msg_.SetAllocated(msg, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.msg_.IsDefault()) {
    _impl_.msg_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg_protocol_pb.chat_publice.msg)
}

// -------------------------------------------------------------------

// server_reply

// string user_name = 1;
inline void server_reply::clear_user_name() {
  _impl_.user_name_.ClearToEmpty();
}
inline const std::string& server_reply::user_name() const {
  // @@protoc_insertion_point(field_get:msg_protocol_pb.server_reply.user_name)
  return _internal_user_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void server_reply::set_user_name(ArgT0&& arg0, ArgT... args) {
 
 _impl_.user_name_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg_protocol_pb.server_reply.user_name)
}
inline std::string* server_reply::mutable_user_name() {
  std::string* _s = _internal_mutable_user_name();
  // @@protoc_insertion_point(field_mutable:msg_protocol_pb.server_reply.user_name)
  return _s;
}
inline const std::string& server_reply::_internal_user_name() const {
  return _impl_.user_name_.Get();
}
inline void server_reply::_internal_set_user_name(const std::string& value) {
  
  _impl_.user_name_.Set(value, GetArenaForAllocation());
}
inline std::string* server_reply::_internal_mutable_user_name() {
  
  return _impl_.user_name_.Mutable(GetArenaForAllocation());
}
inline std::string* server_reply::release_user_name() {
  // @@protoc_insertion_point(field_release:msg_protocol_pb.server_reply.user_name)
  return _impl_.user_name_.Release();
}
inline void server_reply::set_allocated_user_name(std::string* user_name) {
  if (user_name != nullptr) {
    
  } else {
    
  }
  _impl_.user_name_.SetAllocated(user_name, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.user_name_.IsDefault()) {
    _impl_.user_name_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg_protocol_pb.server_reply.user_name)
}

// string info = 2;
inline void server_reply::clear_info() {
  _impl_.info_.ClearToEmpty();
}
inline const std::string& server_reply::info() const {
  // @@protoc_insertion_point(field_get:msg_protocol_pb.server_reply.info)
  return _internal_info();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void server_reply::set_info(ArgT0&& arg0, ArgT... args) {
 
 _impl_.info_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:msg_protocol_pb.server_reply.info)
}
inline std::string* server_reply::mutable_info() {
  std::string* _s = _internal_mutable_info();
  // @@protoc_insertion_point(field_mutable:msg_protocol_pb.server_reply.info)
  return _s;
}
inline const std::string& server_reply::_internal_info() const {
  return _impl_.info_.Get();
}
inline void server_reply::_internal_set_info(const std::string& value) {
  
  _impl_.info_.Set(value, GetArenaForAllocation());
}
inline std::string* server_reply::_internal_mutable_info() {
  
  return _impl_.info_.Mutable(GetArenaForAllocation());
}
inline std::string* server_reply::release_info() {
  // @@protoc_insertion_point(field_release:msg_protocol_pb.server_reply.info)
  return _impl_.info_.Release();
}
inline void server_reply::set_allocated_info(std::string* info) {
  if (info != nullptr) {
    
  } else {
    
  }
  _impl_.info_.SetAllocated(info, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.info_.IsDefault()) {
    _impl_.info_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:msg_protocol_pb.server_reply.info)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace msg_protocol_pb

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_msg_5fprotocol_2eproto