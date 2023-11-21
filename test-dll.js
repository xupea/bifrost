const ffi = require('ffi-napi');

const libm = ffi.Library('dll_path', {
  'get_conversations': [ 'int', [ 'pointer' ] ],
  'set_conversation_event_callback': [ 'void', [ 'pointer' ] ]
});

const code1 = libm.get_conversations((conversations) => {
    console.log(conversations);
});

const code2 = libm.set_conversation_event_callback((event) => {
    // event
    console.log(event);
});