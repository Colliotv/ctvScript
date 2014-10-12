#ifndef Script_h__
# define Script_h__
# define INCLUDED_FROM_SCRIPT

# include "helper/patternConstructor.hh"

namespace cTVScript {
  class script {
  public:
    MAKE_SINGLETON(script,,,);

  public:
#	include "script/symbol.hh"

  public:
#	include "script/callback.hh"
    static std::vector<callback*>& getCallback() {
      return (get()->callbackList);
    }
  private:
    std::vector< callback* > callbackList;

  };

};

#endif
