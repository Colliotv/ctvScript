/*
 * cTV work: ObjectLoadable
 **/
#ifndef ObjectLoadable_h__
# define ObjectLoadable_h__

# include "status.h"

# include "Accessor.hh"

namespace cTVScript{

  class ObjectLoadable : public Loadable{
  private:
    std::map<std::string, Loadable*> childNodes;

  public:
    ObjectLoadable(const std::string& name) : Loadable(name) {}

  public:
    cTVScript::loading_status addObject(Loadable* object, std::string name);

  public: // redefined operands
    virtual Loadable* operator[](const std::string& name);
  };


  class Context : public ObjectLoadable{
  public:
    static cTVScript::loading_status addObject(Loadable* object, std::string name) {
      return (getSelf()->addObject(object, name));
    }

  private: // singleton
    static Context* getSelf();
    Context() : ObjectLoadable("context") {};
    ~Context();
  };
};

#endif
