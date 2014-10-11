/*
 * cTV work: Surveyor
**/
#ifndef Surveyor_H__
# define Surveyor_H__

# include <map>

# include "error.h"
# include "patternConstructor.hh"

# include "Loadable.hh"
# include "Script.hh"

namespace cTVScript {

  class Surveyor {
  private:
    std::map< script::symbol::id, script::callback* > toBeFlushed;

  public:
    MAKE_SINGLETON(Surveyor,,,);

  public:
    static void	update(const Loadable* loadable) {
      std::vector< script::callback* >& callbackList = script::getCallback();

      for (auto callback : callbackList)
	if (callback->refreshValue(loadable))
#if __cplusplus > 199711L
	  get()->toBeFlushed.emplace(std::make_pair(callback->getSymbolId(), callback));
#else
	  get()->toBeFlushed.insert(std::make_pair(callback->getSymbolId(), callback));
#endif
    }
  };

};

#endif
