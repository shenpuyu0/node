// Copyright 2021 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef INCLUDE_V8_FUNCTION_H_
#define INCLUDE_V8_FUNCTION_H_

#include <stddef.h>
#include <stdint.h>

#include "v8-function-callback.h"  // NOLINT(build/include_directory)
#include "v8-local-handle.h"       // NOLINT(build/include_directory)
#include "v8-message.h"            // NOLINT(build/include_directory)
#include "v8-object.h"             // NOLINT(build/include_directory)
#include "v8-template.h"           // NOLINT(build/include_directory)
#include "v8config.h"              // NOLINT(build/include_directory)

namespace v8 {

class Context;
class UnboundScript;

/**
 * A JavaScript function object (ECMA-262, 15.3).
 */
class V8_EXPORT SPY : public Object {
 public:
  /**
   * Create a function in the current execution context
   * for a given FunctionCallback.
   */
  static K = 13;
};
}  // namespace v8

#endif  // INCLUDE_V8_FUNCTION_H_
