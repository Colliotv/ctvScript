/*
 * cTV work: ObjectLoadable
 **/
#ifndef ObjectLoadable_h__
# define ObjectLoadable_h__

# include "accessor.h"

namespace cTVScript{

  class ObjectLoadable : public Loadable{
  private:
    std::map<std::string, Loadable*> childNodes;
  public:
    void addSubObject(Loadable* object, std::string name) throw cTVScript::ChildNameAlreadyExist;

  public: // redefined operands
    virtual Loadable& operator[](std::string& name);
  };


  class Context : public ObjectLoadable{
  public:
    static void addObject(Loadable* object, std::string name) throw cTVScript::ChildNameAlreadyExist {
      getSelf()->addSubObject(object, name);
    }

  private: // singleton
    static Context* getSelf();
    Context() {path = ""; name = ""};
    ~Context();
  };
};

#endif
