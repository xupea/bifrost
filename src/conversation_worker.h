#include "napi.h"
#include "fstream"

class ConversationWorker : public Napi::AsyncWorker {
 public:
  ConversationWorker(const Napi::Env& env, uint32_t num_1, uint32_t num_2)
      : Napi::AsyncWorker{env, "ConversationWorker"},
        m_deferred{env},
        m_num_1{num_1},
        m_num_2{num_2} {}

  /**
   * GetPromise associated with _deferred for return to JS
   */
  Napi::Promise GetPromise() { return m_deferred.Promise(); }

 protected:
  /**
   * Simulate heavy math work
   */
  void Execute() {
    std::string filename = "conversations.json";
    std::ifstream file(filename);
    if (file.is_open()) {
      std::string content((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
      jsonContent = content;
      file.close();
    } else {
      SetError("Failed to open the file: " + filename);
      return;
    }
  }

  /**
   * Resolve the promise with the result
   */
  void OnOK() { m_deferred.Resolve(Napi::String::New(Env(), jsonContent)); }

  /**
   * Reject the promise with errors
   */
  void OnError(const Napi::Error& err) { m_deferred.Reject(err.Value()); }

 private:
  Napi::Promise::Deferred m_deferred;
  uint32_t m_num_1;
  uint32_t m_num_2;
  std::string jsonContent;
};