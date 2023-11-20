const EventEmitter = require("events").EventEmitter;
const sdk = require("bindings")("bifrost");

// utils
const emitter = new EventEmitter();

// 获取最近会话
// sdk.getConversationList(100, 1).then(console.log);

// 监听会话列表变化
emitter.on("conversationListUpdate", console.log);

sdk.callEmit(emitter.emit.bind(emitter));

setInterval(() => console.log(Date.now()), 1000);
