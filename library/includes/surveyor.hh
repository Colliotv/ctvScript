/*
 * cTV work: Surveyor
**/
#ifndef Surveyor_H__
# define Surveyor_H__

# inlcude "error.h"

# include "Loader.hh"

# include "accessibles.hh"

namespace cTVScript {

  /* stock a list to cTVScript:ScriptAccessibles */
  class Surveyor {

  public:
    static Surveyor* get() { // need to be singleton
      static Surveyor* surveyor;
      return (!surveyor ?
	      surveyor = new Surveyor() :
	      surveyor);
    }
    static void destroy() {
      Surveyor* surveyor;
      delete surveyor;
    }
  private:
    Surveyor();
    ~Surveyor();


  private:
    bool CallbackCallOnQualifiedEvents; // if enabled surveyor will automaticaly call scripted callback if conditions are OK
    std::queue<cTVScript::callbackHandle> callbackQueue;

  public:
    void	enableCallbackCallOnQualifiedEvents(bool = true);
    void	flushEvents();
    void	treatEvents() throw ScriptError; // need to be specificated
  }
}

#endif
