/*
 * cTV work: Loader
 **/
#ifndef Loader_H__
# define Loader_H__

# include <string>
# include <map>

# include "error.h"

# include "utils.h"

# include "Accessor.hh"

namespace cTVScript {

  class Loader {
  public:
    static Loader* get() {
      static Loader* loader;
      return (!loader ? 
	      loader = new Loader():
	      loader);
    }
    static void	destroy() {
      Loader* loader = get();
      delete loader;
    }
  private:
    Loader();
    ~Loader();
  };
};

#endif
