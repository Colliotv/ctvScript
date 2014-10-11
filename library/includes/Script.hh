#ifndef Script_h__
# define Script_h__
# define INCLUDED_FROM_SCRIPT

# include "Loadable.hh"

# include "patternConstructor.hh"

namespace cTVScript {
  class script {
  public:
    MAKE_SINGLETON(script,,,);

  public:
    class symbol { public: typedef int id; };

  public:
#   include "ScriptCallback.hh"
    static std::vector<callback*>& getCallback() {
      return (get()->callbackList);
    }
  private:
    std::vector< callback* > callbackList;

  };

};

#endif
