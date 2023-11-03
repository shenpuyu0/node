const {exposeNamespace,} = require('internal/util');

const config = internalBinding('config');

// 添加logger
function createGlobalLogger() {
    const consoleFromNode = require('spy/internal/console/logger');

    if (config.hasInspector) {
        const inspector = require('internal/util/inspector');
        // TODO(joyeecheung): postpone this until the first time inspector
        // is activated.
        inspector.wrapConsole(consoleFromNode);
        const {setConsoleExtensionInstaller} = internalBinding('inspector');
        // Setup inspector command line API.
        setConsoleExtensionInstaller(inspector.installConsoleExtensions);
    }
    return consoleFromNode;
}

exposeNamespace(globalThis, 'logger', createGlobalLogger());

// 初始化Logger
const globalLogger = require('spy/internal/console/logger');
const {initializeGlobalConsole} = require('internal/console/constructor');

initializeGlobalConsole(globalLogger);
