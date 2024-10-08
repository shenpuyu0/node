//
// Created by mac on 2023/11/13.
//

#include "spy_plugins.h"
#include "ada.h"
#include "env-inl.h"
#include "node_errors.h"
#include "node_external_reference.h"
#include "simdutf.h"
#include "string_bytes.h"
#include "v8.h"

#include <cstdint>

namespace node {
namespace spy_space {

using v8::ArrayBuffer;
using v8::BackingStore;
using v8::Context;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::MaybeLocal;
using v8::Object;
using v8::ObjectTemplate;
using v8::SPY;
using v8::String;
using v8::Uint8Array;
using v8::Value;
using v8::Boolean;

void BindingData::MemoryInfo(MemoryTracker* tracker) const {
  tracker->TrackField("spy_into_results_buffer", spy_into_results_buffer_);
}

BindingData::BindingData(Realm* realm,
                         v8::Local<v8::Object> object,
                         InternalFieldInfo* info)
    : SnapshotableObject(realm, object, type_int),
      spy_into_results_buffer_(realm->isolate(),
                               kSpyIntoResultsLength,
                               MAYBE_FIELD_PTR(info, spy_into_results_buffer)) {
  if (info == nullptr) {
    object
        ->Set(realm->context(),
              FIXED_ONE_BYTE_STRING(realm->isolate(), "spyIntoResults"),
              spy_into_results_buffer_.GetJSArray())
        .Check();
  } else {
    spy_into_results_buffer_.Deserialize(realm->context());
  }
  spy_into_results_buffer_.MakeWeak();
}

bool BindingData::PrepareForSerialization(Local<Context> context,
                                          v8::SnapshotCreator* creator) {
  DCHECK_NULL(internal_field_info_);
  internal_field_info_ = InternalFieldInfoBase::New<InternalFieldInfo>(type());
  internal_field_info_->spy_into_results_buffer =
      spy_into_results_buffer_.Serialize(context, creator);
  // Return true because we need to maintain the reference to the binding from
  // JS land.
  return true;
}

InternalFieldInfoBase* BindingData::Serialize(int index) {
  DCHECK_IS_SNAPSHOT_SLOT(index);
  InternalFieldInfo* info = internal_field_info_;
  internal_field_info_ = nullptr;
  return info;
}

void BindingData::Deserialize(Local<Context> context,
                              Local<Object> holder,
                              int index,
                              InternalFieldInfoBase* info) {
  DCHECK_IS_SNAPSHOT_SLOT(index);
  v8::HandleScope scope(context->GetIsolate());
  Realm* realm = Realm::GetCurrent(context);
  // Recreate the buffer in the constructor.
  InternalFieldInfo* casted_info = static_cast<InternalFieldInfo*>(info);
  BindingData* binding =
      realm->AddBindingData<BindingData>(holder, casted_info);
  CHECK_NOT_NULL(binding);
}

void BindingData::EncodeInto(const FunctionCallbackInfo<Value>& args) {
  CHECK_GE(args.Length(), 2);
  CHECK(args[0]->IsString());
  CHECK(args[1]->IsUint8Array());

  Realm* realm = Realm::GetCurrent(args);
  Isolate* isolate = realm->isolate();
  BindingData* binding_data = realm->GetBindingData<BindingData>();

  Local<String> source = args[0].As<String>();

  Local<Uint8Array> dest = args[1].As<Uint8Array>();
  Local<ArrayBuffer> buf = dest->Buffer();
  char* write_result = static_cast<char*>(buf->Data()) + dest->ByteOffset();
  size_t dest_length = dest->ByteLength();

  int nchars;
  int written = source->WriteUtf8(
      isolate,
      write_result,
      dest_length,
      &nchars,
      String::NO_NULL_TERMINATION | String::REPLACE_INVALID_UTF8);

  binding_data->spy_into_results_buffer_[0] = nchars;
  binding_data->spy_into_results_buffer_[1] = written;
}

void BindingData::SetNative(const v8::FunctionCallbackInfo<v8::Value>& args) {
  //  Environment* env = Environment::GetCurrent(args);

  args.GetReturnValue().Set(SPY::SetNative(args));
}

void BindingData::CreatePerIsolateProperties(IsolateData* isolate_data,
                                             Local<ObjectTemplate> target) {
  Isolate* isolate = isolate_data->isolate();
  SetMethod(isolate, target, "encodeInto", EncodeInto);
  SetMethodNoSideEffect(isolate, target, "setNative", SetNative);
}

void BindingData::CreatePerContextProperties(Local<Object> target,
                                             Local<Value> unused,
                                             Local<Context> context,
                                             void* priv) {
  Realm* realm = Realm::GetCurrent(context);
  realm->AddBindingData<BindingData>(target);
}

void BindingData::RegisterTimerExternalReferences(
    ExternalReferenceRegistry* registry) {
  registry->Register(EncodeInto);
  registry->Register(SetNative);
}

}  // namespace spy_space
}  // namespace node

NODE_BINDING_CONTEXT_AWARE_INTERNAL(
    spy, node::spy_space::BindingData::CreatePerContextProperties)
NODE_BINDING_PER_ISOLATE_INIT(
    spy, node::spy_space::BindingData::CreatePerIsolateProperties)
NODE_BINDING_EXTERNAL_REFERENCE(
    spy, node::spy_space::BindingData::RegisterTimerExternalReferences)
