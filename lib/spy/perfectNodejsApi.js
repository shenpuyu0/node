const {async_id_symbol} = require("internal/timers");
let {
    globalThis,
    ObjectGetOwnPropertySymbols
} = primordials;
const getOwnPropertySymbols = ObjectGetOwnPropertySymbols;
ObjectGetOwnPropertySymbols = function getOwnPropertySymbols(){
    let result = getOwnPropertySymbols.apply(this, arguments);
    return result.filter(x => !(x.description.startsWith("nodejs") || x.description.startsWith("k")))
}

// 需在lib/timer.js中修改setTimeout方法返回值
// 由 return timeout; ==> return timeout[async_id_symbol];