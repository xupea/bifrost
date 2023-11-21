#include <napi.h>
#include "conversation_worker.h"

Napi::Value getConversationList(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (!info[0].IsNumber())
  {
    Napi::TypeError::New(env, "num1 must be a number")
        .ThrowAsJavaScriptException();
    return env.Undefined();
  }
  uint32_t num_1 = info[0].As<Napi::Number>().Uint32Value();

  if (!info[1].IsNumber())
  {
    Napi::TypeError::New(env, "num2 must be a number")
        .ThrowAsJavaScriptException();
    return env.Undefined();
  }
  uint32_t num_2 = info[1].As<Napi::Number>().Uint32Value();

  ConversationWorker *worker = new ConversationWorker(env, num_1, num_2);
  worker->Queue();
  return worker->GetPromise();
}

Napi::FunctionReference sessionListChangeCallback;

Napi::Value watchConversationList(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Function emit = info[0].As<Napi::Function>();

  // 存储回调函数的引用，以便后续调用
  sessionListChangeCallback = Napi::Persistent(emit);

  return env.Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "getConversationList"),
              Napi::Function::New(env, getConversationList));
  exports.Set(Napi::String::New(env, "watchConversationList"),
              Napi::Function::New(env, watchConversationList));
  return exports;
}

NODE_API_MODULE(hello, Init)