//
// Created by mac on 2023/11/13.
//

#include "v8.h"
namespace node {

using v8::Isolate;
using v8::FunctionCallbackInfo;
using v8::SPY;

void HelloWorld(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  printf("Hello, World!\n");
}
void SetNative(const v8::FunctionCallbackInfo<v8::Value>& args){
  SPY::Setnative(args)
}

//void Initialize(v8::Local<v8::Object> exports) {
//  NODE_SET_METHOD(exports, "hello", HelloWorld);
//}

//NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
} // node