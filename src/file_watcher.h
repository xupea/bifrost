#include <napi.h>
#include <fstream>
#include <unordered_map>

class FileWatcher {
public:
  FileWatcher(const std::string& filename, Napi::Function& callback)
    : filename(filename), callback(callback), running(false) {}

  void Start() {
    if (!running) {
      running = true;
      worker = new Napi::ThreadSafeFunction(
        callback, "FileWatcher", 0, 1, nullptr, Finalizer);
      WatchFileChanges();
    }
  }

  void Stop() {
    if (running) {
      running = false;
      delete worker;
    }
  }

private:
  static void WatchFileChangesThread(void* arg) {
    auto watcher = static_cast<FileWatcher*>(arg);
    std::ifstream file(watcher->filename);
    std::unordered_map<std::string, long> fileStats;

    while (watcher->running) {
      if (file.is_open()) {
        file.clear();
        file.seekg(0);
        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

        if (fileStats.find(content) == fileStats.end()) {
          // File content has changed
          fileStats[content] = 1;
          Napi::Buffer<char> buffer = Napi::Buffer<char>::New(
            watcher->callback.Env(), content.data(), content.length());
          watcher->worker->BlockingCall(&buffer, OnFileChanged);
        }
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    file.close();
  }

  static void OnFileChanged(Napi::Env env, Napi::Function jsCallback,
                            Napi::Buffer<char> buffer) {
    jsCallback.Call({buffer});
  }

  static void Finalizer(Napi::Env env, void* data, void* hint) {
    delete static_cast<Napi::ThreadSafeFunction*>(data);
  }

  std::string filename;
  Napi::Function callback;
  bool running;
  Napi::ThreadSafeFunction* worker;

  void WatchFileChanges() {
    std::thread thread(WatchFileChangesThread, this);
    thread.detach();
  }
};