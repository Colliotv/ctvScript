/*
 * cTV work: Loader
 **/
#ifndef Loader_H__
# define Loader_H__

# include <string>
# include <map>

# include "status.h"
# include "error.h"

# include "utils.h"

# include "accessor.hh"

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

    /*
     * method will run thought by director // ask for prefered (one call or in loop)
     *  return (
     *		NO_PERMISSIONS_FILE (DIR)  : no permissions
     *		INVALID_FILE : file is invalid (wrong header, not a script file)
     *		CORRUPTED_SCRIPT : some part can't be deducedn tables are empty
     *		EMPTY_DIRECTORY : directory doesn't contain anything
     *		SUCCESS
     *		)
     */
  public:
    cTVScript::scriptStatus loadScriptFromDirectory( bool skipError = false );
    cTVScript::scriptStatus loadScriptFromDirectory( std::string, bool skipError = false );
    

  private:
    cTVscript::scriptTable< cTVScript::functionHandleId, cTVScript::functionCode* > scripts;

  };


};

#endif
