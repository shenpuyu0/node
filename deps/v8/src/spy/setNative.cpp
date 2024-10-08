

#include "include/v8-spy.h"
#include "include/v8-callbacks.h"
#include "src/api/api-inl.h"

namespace v8 {

Local<Boolean> SPY::SetNative(const FunctionCallbackInfo<Value>& args) {
  //  PREPARE_FOR_EXECUTION(context, SPY, SetNative, Boolean);
  Isolate* v8_isolate = args.GetIsolate();

  i::Isolate* i_isolate = reinterpret_cast<i::Isolate*>(v8_isolate);
  if (args.Length() < 1) {
    i_isolate->ScheduleThrow(*i_isolate->factory()->NewError(
        i_isolate->error_function(),  // Uncaught TypeError:
        i_isolate->factory()->InternalizeUtf8String(
            "Failed to execute 'SetNative' on 'Window': 1 argument required, "
            "but only 0 present.")));
  }
  if (!args[0]->IsFunction()) {
    i_isolate->ScheduleThrow(*i_isolate->factory()->NewError(
        i_isolate->error_function(),  // Uncaught TypeError:
        i_isolate->factory()->InternalizeUtf8String(
            "Failed to execute 'SetNative' on 'Window': The passed in "
            "parameter must be a function.")));
  };

  i::Tagged<i::Object> obj = *Utils::OpenHandle(*args[0]);
  if (i::IsJSFunction(obj)) {
    // TODO debug时预处理会直接处理将
    i::Handle<i::JSFunction> function =
        i::Handle<i::JSFunction>::cast(Utils::OpenHandle(*args[0]));

    // i::Isolate* i_isolate = function->GetIsolate();
    i::Handle<i::SharedFunctionInfo> shared_info(function->shared(), i_isolate);

    // 已经是 native code 的 function 再次设置会导致失败
    if (!shared_info->IsUserJavaScript() || !shared_info->HasSourceCode()) {
      return Boolean::New(v8_isolate, false);
    }
    i::Tagged<i::Object> script_obj = shared_info->script();
    i::Tagged<i::Script> script = i::Script::cast(script_obj);
    script->set_type(i::Script::Type::kNative);
    return Boolean::New(v8_isolate, true);
  } else if (i::IsJSBoundFunction(obj)) {
    i_isolate->ScheduleThrow(*i_isolate->factory()->NewError(
        i_isolate->error_function(),
        i_isolate->factory()->InternalizeUtf8String(
            "Bind Function Can't Call Function SetNative")));
  };

  return Boolean::New(v8_isolate, false);
}
}  // namespace v8