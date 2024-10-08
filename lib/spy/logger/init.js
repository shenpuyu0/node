const {exposeNamespace,} = require('internal/util');

const config = internalBinding('config');

// 添加logger
function createGlobalLogger() {
    const consoleFromNode = require('spy/internal/logger/global');

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
const globalLogger = require('spy/internal/logger/global');
const {initializeGlobalConsole} = require('internal/console/constructor');

initializeGlobalConsole(globalLogger);


module.exports = {
    logger: {
        debug: globalLogger.log.bind(globalLogger.log, '\x1B[36m%s\x1B[0m'),
        info: globalLogger.log.bind(globalLogger.log),
        warn: globalLogger.log.bind(globalLogger.log, '\x1B[33m%s\x1B[0m'),
        error: globalLogger.log.bind(globalLogger.log, '\x1B[31m%s\x1B[0m'),
        success: globalLogger.log.bind(globalLogger.log, '\x1B[32m%s\x1B[0m'),
        logger: globalLogger,
    }
}
