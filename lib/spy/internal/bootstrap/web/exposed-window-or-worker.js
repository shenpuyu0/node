'use strict';

/**
 * This file exposes web interfaces that is defined with the WebIDL
 * Exposed=Window + Exposed=(Window,Worker) extended attribute or exposed in
 * WindowOrWorkerGlobalScope mixin.
 * See more details at https://webidl.spec.whatwg.org/#Exposed and
 * https://html.spec.whatwg.org/multipage/webappapis.html#windoworworkerglobalscope.
 */

const {
  globalThis,
} = primordials;

const {
  defineOperation,
  defineLazyProperties,
  defineReplaceableLazyAttribute,
  exposeLazyInterfaces,
  exposeNamespace,
} = require('internal/util');
// 懒加载 Window 对象
exposeLazyInterfaces(globalThis, 'spy/internal/Window', ['Window']);
globalThis.__proto__ = Window.prototype;
exposeLazyInterfaces(globalThis, 'spy/internal/logger/init', ['logger']);

module.exports = {}

// https://html.spec.whatwg.org/multipage/system-state.html#the-navigator-object
// exposeLazyInterfaces(globalThis, 'internal/navigator', ['Navigator']);
// defineReplaceableLazyAttribute(globalThis, 'internal/navigator', ['navigator'], false);
