//
// Created by mac on 2023/11/20.
//

#ifndef NODE_NODE_SPY_H
#define NODE_NODE_SPY_H

#if defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#include <cinttypes>
#include "aliased_buffer.h"
#include "node_snapshotable.h"
#include "v8-fast-api-calls.h"

namespace node {
class ExternalReferenceRegistry;

namespace spy_space {
class BindingData : public SnapshotableObject {
 public:
  struct InternalFieldInfo : public node::InternalFieldInfoBase {
    AliasedBufferIndex spy_into_results_buffer;
  };

  BindingData(Realm* realm,
              v8::Local<v8::Object> obj,
              InternalFieldInfo* info = nullptr);
  SERIALIZABLE_OBJECT_METHODS()
  SET_BINDING_ID(spy_binding_data)

  void MemoryInfo(MemoryTracker* tracker) const override;
  SET_SELF_SIZE(BindingData)
  SET_MEMORY_INFO_NAME(BindingData)

  static void EncodeInto(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void SetNative(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void CreatePerIsolateProperties(IsolateData* isolate_data,
                                         v8::Local<v8::ObjectTemplate> target);
  static void CreatePerContextProperties(v8::Local<v8::Object> target,
                                         v8::Local<v8::Value> unused,
                                         v8::Local<v8::Context> context,
                                         void* priv);
  static void RegisterTimerExternalReferences(
      ExternalReferenceRegistry* registry);

 private:
  static constexpr size_t kSpyIntoResultsLength = 2;
  AliasedUint32Array spy_into_results_buffer_;
  InternalFieldInfo* internal_field_info_ = nullptr;
};

}  // namespace encoding_binding

}  // namespace node

#endif  // defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#endif  // NODE_NODE_SPY_H
