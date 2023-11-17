const { SetNative, HelloWorld } = internalBinding('spy');
global.SetNative = SetNative;
global.HelloWorld = HelloWorld;