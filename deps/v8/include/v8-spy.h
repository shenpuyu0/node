//
// Created by mac on 2023/11/15.
//

#ifndef NODE_V8_SPY_H
#define NODE_V8_SPY_H


#include "v8-function.h"
#include "v8-function-callback.h"

#include "v8-local-handle.h"  // NOLINT(build/include_directory)
#include "v8config.h"         // NOLINT(build/include_directory)



namespace v8 {

class Value;

class V8_EXPORT SPY {
 public:
  static V8_WARN_UNUSED_RESULT Maybe<bool> SetNative(const FunctionCallbackInfo<Value>& args);
};

}  // namespace v8
#endif  // NODE_V8_SPY_H
