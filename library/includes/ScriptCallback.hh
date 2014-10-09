#ifndef ScriptCallback_h__
# define ScriptCallback_h__

namespace cTVScript {
  class ScriptCallback {
  private:
    struct ValueState {
      ValueState(const std::string& _path) : isReady(false), path(_path) {}
      bool		isReady;
      std::string	path;
    };
    std::vector<ValueState*> associatedValue;

  public:
    ScriptCallback() {}
    ~ScriptCallback() { for (auto k: associatedValue) delete k; }
  };
};

#endif
