// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: address_book.proto

#ifndef PROTOBUF_address_5fbook_2eproto__INCLUDED
#define PROTOBUF_address_5fbook_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include "computer.pb.h"
// @@protoc_insertion_point(includes)

namespace protobuf_address_5fbook_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void InitDefaultsComputerGroupImpl();
void InitDefaultsComputerGroup();
void InitDefaultsAddressBookImpl();
void InitDefaultsAddressBook();
inline void InitDefaults() {
  InitDefaultsComputerGroup();
  InitDefaultsAddressBook();
}
}  // namespace protobuf_address_5fbook_2eproto
namespace aspia {
namespace proto {
class AddressBook;
class AddressBookDefaultTypeInternal;
extern AddressBookDefaultTypeInternal _AddressBook_default_instance_;
class ComputerGroup;
class ComputerGroupDefaultTypeInternal;
extern ComputerGroupDefaultTypeInternal _ComputerGroup_default_instance_;
}  // namespace proto
}  // namespace aspia
namespace aspia {
namespace proto {

// ===================================================================

class ComputerGroup : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:aspia.proto.ComputerGroup) */ {
 public:
  ComputerGroup();
  virtual ~ComputerGroup();

  ComputerGroup(const ComputerGroup& from);

  inline ComputerGroup& operator=(const ComputerGroup& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ComputerGroup(ComputerGroup&& from) noexcept
    : ComputerGroup() {
    *this = ::std::move(from);
  }

  inline ComputerGroup& operator=(ComputerGroup&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ComputerGroup& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ComputerGroup* internal_default_instance() {
    return reinterpret_cast<const ComputerGroup*>(
               &_ComputerGroup_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ComputerGroup* other);
  friend void swap(ComputerGroup& a, ComputerGroup& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ComputerGroup* New() const PROTOBUF_FINAL { return New(NULL); }

  ComputerGroup* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const ComputerGroup& from);
  void MergeFrom(const ComputerGroup& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ComputerGroup* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .aspia.proto.Computer computer = 1;
  int computer_size() const;
  void clear_computer();
  static const int kComputerFieldNumber = 1;
  const ::aspia::proto::Computer& computer(int index) const;
  ::aspia::proto::Computer* mutable_computer(int index);
  ::aspia::proto::Computer* add_computer();
  ::google::protobuf::RepeatedPtrField< ::aspia::proto::Computer >*
      mutable_computer();
  const ::google::protobuf::RepeatedPtrField< ::aspia::proto::Computer >&
      computer() const;

  // repeated .aspia.proto.ComputerGroup group = 2;
  int group_size() const;
  void clear_group();
  static const int kGroupFieldNumber = 2;
  const ::aspia::proto::ComputerGroup& group(int index) const;
  ::aspia::proto::ComputerGroup* mutable_group(int index);
  ::aspia::proto::ComputerGroup* add_group();
  ::google::protobuf::RepeatedPtrField< ::aspia::proto::ComputerGroup >*
      mutable_group();
  const ::google::protobuf::RepeatedPtrField< ::aspia::proto::ComputerGroup >&
      group() const;

  // string name = 3;
  void clear_name();
  static const int kNameFieldNumber = 3;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // string comment = 4;
  void clear_comment();
  static const int kCommentFieldNumber = 4;
  const ::std::string& comment() const;
  void set_comment(const ::std::string& value);
  #if LANG_CXX11
  void set_comment(::std::string&& value);
  #endif
  void set_comment(const char* value);
  void set_comment(const char* value, size_t size);
  ::std::string* mutable_comment();
  ::std::string* release_comment();
  void set_allocated_comment(::std::string* comment);

  // @@protoc_insertion_point(class_scope:aspia.proto.ComputerGroup)
 private:

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::aspia::proto::Computer > computer_;
  ::google::protobuf::RepeatedPtrField< ::aspia::proto::ComputerGroup > group_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr comment_;
  mutable int _cached_size_;
  friend struct ::protobuf_address_5fbook_2eproto::TableStruct;
  friend void ::protobuf_address_5fbook_2eproto::InitDefaultsComputerGroupImpl();
};
// -------------------------------------------------------------------

class AddressBook : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:aspia.proto.AddressBook) */ {
 public:
  AddressBook();
  virtual ~AddressBook();

  AddressBook(const AddressBook& from);

  inline AddressBook& operator=(const AddressBook& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  AddressBook(AddressBook&& from) noexcept
    : AddressBook() {
    *this = ::std::move(from);
  }

  inline AddressBook& operator=(AddressBook&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const AddressBook& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AddressBook* internal_default_instance() {
    return reinterpret_cast<const AddressBook*>(
               &_AddressBook_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(AddressBook* other);
  friend void swap(AddressBook& a, AddressBook& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AddressBook* New() const PROTOBUF_FINAL { return New(NULL); }

  AddressBook* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const AddressBook& from);
  void MergeFrom(const AddressBook& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(AddressBook* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .aspia.proto.ComputerGroup root_group = 1;
  bool has_root_group() const;
  void clear_root_group();
  static const int kRootGroupFieldNumber = 1;
  const ::aspia::proto::ComputerGroup& root_group() const;
  ::aspia::proto::ComputerGroup* release_root_group();
  ::aspia::proto::ComputerGroup* mutable_root_group();
  void set_allocated_root_group(::aspia::proto::ComputerGroup* root_group);

  // @@protoc_insertion_point(class_scope:aspia.proto.AddressBook)
 private:

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::aspia::proto::ComputerGroup* root_group_;
  mutable int _cached_size_;
  friend struct ::protobuf_address_5fbook_2eproto::TableStruct;
  friend void ::protobuf_address_5fbook_2eproto::InitDefaultsAddressBookImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ComputerGroup

// repeated .aspia.proto.Computer computer = 1;
inline int ComputerGroup::computer_size() const {
  return computer_.size();
}
inline const ::aspia::proto::Computer& ComputerGroup::computer(int index) const {
  // @@protoc_insertion_point(field_get:aspia.proto.ComputerGroup.computer)
  return computer_.Get(index);
}
inline ::aspia::proto::Computer* ComputerGroup::mutable_computer(int index) {
  // @@protoc_insertion_point(field_mutable:aspia.proto.ComputerGroup.computer)
  return computer_.Mutable(index);
}
inline ::aspia::proto::Computer* ComputerGroup::add_computer() {
  // @@protoc_insertion_point(field_add:aspia.proto.ComputerGroup.computer)
  return computer_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::aspia::proto::Computer >*
ComputerGroup::mutable_computer() {
  // @@protoc_insertion_point(field_mutable_list:aspia.proto.ComputerGroup.computer)
  return &computer_;
}
inline const ::google::protobuf::RepeatedPtrField< ::aspia::proto::Computer >&
ComputerGroup::computer() const {
  // @@protoc_insertion_point(field_list:aspia.proto.ComputerGroup.computer)
  return computer_;
}

// repeated .aspia.proto.ComputerGroup group = 2;
inline int ComputerGroup::group_size() const {
  return group_.size();
}
inline void ComputerGroup::clear_group() {
  group_.Clear();
}
inline const ::aspia::proto::ComputerGroup& ComputerGroup::group(int index) const {
  // @@protoc_insertion_point(field_get:aspia.proto.ComputerGroup.group)
  return group_.Get(index);
}
inline ::aspia::proto::ComputerGroup* ComputerGroup::mutable_group(int index) {
  // @@protoc_insertion_point(field_mutable:aspia.proto.ComputerGroup.group)
  return group_.Mutable(index);
}
inline ::aspia::proto::ComputerGroup* ComputerGroup::add_group() {
  // @@protoc_insertion_point(field_add:aspia.proto.ComputerGroup.group)
  return group_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::aspia::proto::ComputerGroup >*
ComputerGroup::mutable_group() {
  // @@protoc_insertion_point(field_mutable_list:aspia.proto.ComputerGroup.group)
  return &group_;
}
inline const ::google::protobuf::RepeatedPtrField< ::aspia::proto::ComputerGroup >&
ComputerGroup::group() const {
  // @@protoc_insertion_point(field_list:aspia.proto.ComputerGroup.group)
  return group_;
}

// string name = 3;
inline void ComputerGroup::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ComputerGroup::name() const {
  // @@protoc_insertion_point(field_get:aspia.proto.ComputerGroup.name)
  return name_.GetNoArena();
}
inline void ComputerGroup::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:aspia.proto.ComputerGroup.name)
}
#if LANG_CXX11
inline void ComputerGroup::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:aspia.proto.ComputerGroup.name)
}
#endif
inline void ComputerGroup::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:aspia.proto.ComputerGroup.name)
}
inline void ComputerGroup::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:aspia.proto.ComputerGroup.name)
}
inline ::std::string* ComputerGroup::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:aspia.proto.ComputerGroup.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ComputerGroup::release_name() {
  // @@protoc_insertion_point(field_release:aspia.proto.ComputerGroup.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ComputerGroup::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:aspia.proto.ComputerGroup.name)
}

// string comment = 4;
inline void ComputerGroup::clear_comment() {
  comment_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ComputerGroup::comment() const {
  // @@protoc_insertion_point(field_get:aspia.proto.ComputerGroup.comment)
  return comment_.GetNoArena();
}
inline void ComputerGroup::set_comment(const ::std::string& value) {
  
  comment_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:aspia.proto.ComputerGroup.comment)
}
#if LANG_CXX11
inline void ComputerGroup::set_comment(::std::string&& value) {
  
  comment_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:aspia.proto.ComputerGroup.comment)
}
#endif
inline void ComputerGroup::set_comment(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  comment_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:aspia.proto.ComputerGroup.comment)
}
inline void ComputerGroup::set_comment(const char* value, size_t size) {
  
  comment_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:aspia.proto.ComputerGroup.comment)
}
inline ::std::string* ComputerGroup::mutable_comment() {
  
  // @@protoc_insertion_point(field_mutable:aspia.proto.ComputerGroup.comment)
  return comment_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ComputerGroup::release_comment() {
  // @@protoc_insertion_point(field_release:aspia.proto.ComputerGroup.comment)
  
  return comment_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ComputerGroup::set_allocated_comment(::std::string* comment) {
  if (comment != NULL) {
    
  } else {
    
  }
  comment_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), comment);
  // @@protoc_insertion_point(field_set_allocated:aspia.proto.ComputerGroup.comment)
}

// -------------------------------------------------------------------

// AddressBook

// .aspia.proto.ComputerGroup root_group = 1;
inline bool AddressBook::has_root_group() const {
  return this != internal_default_instance() && root_group_ != NULL;
}
inline void AddressBook::clear_root_group() {
  if (GetArenaNoVirtual() == NULL && root_group_ != NULL) {
    delete root_group_;
  }
  root_group_ = NULL;
}
inline const ::aspia::proto::ComputerGroup& AddressBook::root_group() const {
  const ::aspia::proto::ComputerGroup* p = root_group_;
  // @@protoc_insertion_point(field_get:aspia.proto.AddressBook.root_group)
  return p != NULL ? *p : *reinterpret_cast<const ::aspia::proto::ComputerGroup*>(
      &::aspia::proto::_ComputerGroup_default_instance_);
}
inline ::aspia::proto::ComputerGroup* AddressBook::release_root_group() {
  // @@protoc_insertion_point(field_release:aspia.proto.AddressBook.root_group)
  
  ::aspia::proto::ComputerGroup* temp = root_group_;
  root_group_ = NULL;
  return temp;
}
inline ::aspia::proto::ComputerGroup* AddressBook::mutable_root_group() {
  
  if (root_group_ == NULL) {
    root_group_ = new ::aspia::proto::ComputerGroup;
  }
  // @@protoc_insertion_point(field_mutable:aspia.proto.AddressBook.root_group)
  return root_group_;
}
inline void AddressBook::set_allocated_root_group(::aspia::proto::ComputerGroup* root_group) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete root_group_;
  }
  if (root_group) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      root_group = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, root_group, submessage_arena);
    }
    
  } else {
    
  }
  root_group_ = root_group;
  // @@protoc_insertion_point(field_set_allocated:aspia.proto.AddressBook.root_group)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace aspia

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_address_5fbook_2eproto__INCLUDED
