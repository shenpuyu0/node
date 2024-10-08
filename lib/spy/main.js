

const {
    globalThis,
    ObjectDefineProperty,
    ObjectSetPrototypeOf
} = primordials;

const {
    defineOperation,
    defineLazyProperties,
    defineReplaceableLazyAttribute,
    exposeLazyInterfaces,
    exposeNamespace,
} = require('internal/util');

const {initEventTarget} = require("internal/event_target");

// Window原型
exposeLazyInterfaces(globalThis, 'spy/internal/Window', ['Window']);

// let window = new Window();
// for (let i in globalThis){
//     window[i] = globalThis[i]
// }
// ObjectDefineProperty(globalThis, "window", {
//     get(){return window},
//     enumerable:true, configurable:false,
// })
globalThis.__proto__ = Window.prototype;
initEventTarget(globalThis);

globalThis.internalBinding = internalBinding;

// 自定义的C++插件
globalThis["spy"] = internalBinding("spy");


// logger对象
exposeLazyInterfaces(globalThis["spy"], 'spy/internal/logger/init', ['logger']);


// 修改完善nodejs提供的API
require("spy/perfectNodejsApi")