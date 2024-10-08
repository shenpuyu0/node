
const {
    // spy,
    ObjectDefineProperty,
    ObjectDefineProperties,
    SymbolToStringTag,
} = primordials
const { EventTarget } = require('internal/event_target')
class WindowProperties extends EventTarget{}
delete WindowProperties.prototype.constructor;

ObjectDefineProperty(WindowProperties.prototype, SymbolToStringTag, {
    value: "WindowProperties",
    configurable: true,
    writable: false,
    enumerable: false
})
// spy.safefunction(WindowProperties)
class Window extends WindowProperties{
    static PERSISTENT=1
    static TEMPORARY=0
    constructor() {
        // if (arguments[0] !== spy.kInitialize){
        //     throw new TypeError(spy.Illegal_Constructor_Error)
        // }
        super();
        ObjectDefineProperty(this, SymbolToStringTag, {
            value: "Window",
            configurable: true,
            writable: false,
            enumerable: false
        })
    }
}

ObjectDefineProperties(Window.prototype, {
    PERSISTENT:{enumerable:true, configurable:true, writable:true, value:Window.PERSISTENT},
    TEMPORARY:{enumerable:true, configurable:true, writable:true, value:Window.TEMPORARY},
})
// spy.safefunction(Window)
ObjectDefineProperty(Window.prototype, SymbolToStringTag, {
    value: "Window",
    configurable: true,
    writable: false,
    enumerable: false
})

module.exports = {
    Window
}