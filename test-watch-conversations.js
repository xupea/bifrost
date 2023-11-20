const sdk = require("bindings")("bifrost");

sdk.watchConversationList((item) => {
  console.log(item);
});
