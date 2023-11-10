//
// Created by mac on 2023/11/9.
//

#ifndef NODE_SET_NATIVE_H
#define NODE_SET_NATIVE_H
#include "src/objects/shared-function-info.h"

namespace v8 {
namespace internal {

//
bool SharedFunctionInfo::SetNativeType() const {
  Tagged<Object> script_obj = script();
  if (IsUndefined(script_obj)) return false;
  Tagged<Script> script = Script::cast(script_obj);
  script->set_type(Script::Type::kNative);
  return true;
}

} // internal
} // v8
#endif  // NODE_SET_NATIVE_H
