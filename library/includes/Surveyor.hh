/*
 * cTV work: Surveyor
**/
#ifndef Surveyor_H__
# define Surveyor_H__

# include "error.h"
# include "patternConstructor.hh"

# include "Loadable.hh"

# include "ScriptCallback.hh"

namespace cTVScript {

  class Surveyor {
  public:
    MAKE_SINGLETON(Surveyor,,,);

  public:
    void	update(const Loadable*) {
      
    }
  };

};

#endif
