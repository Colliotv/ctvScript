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

  /*
   * The loader is the main classs of the ctv script:
   * It Store script code
   *
   */
  class Loader {
  public:
    static Loader* get() { // singleton allocation
      static Loader* loader;
      return (!loader ? 
	      loader = new Loader():
	      loader);
    }
    static void	destroy() { // singleton destroyer
      Loader* loader = get();
      delete loader;
    }
  private:
    Loader();
    ~Loader();
  };
};

#endif
