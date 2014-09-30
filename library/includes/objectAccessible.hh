/*
 * cTV work: ObjectAccessible
 **/
#ifndef ObjectAccessible.h
# define ObjectAccessible.h

# include "accessor.h"

namespace cTVScript{

  class ObjectAccessible : public Accessible{
  private:
    std::map<std::string, Accessible*> childNodes;
  public:
    void addSubObject(Accessible* object, std::string name) throw cTVScript::ChildNameAlreadyExist;

  public: // redefined operands
    virtual Accessible& operator[](std::string& name);
  };


  class Context : public ObjectAccessible{
  public:
    static void addObject(Accessible* object, std::string name) throw cTVScript::ChildNameAlreadyExist {
      getSelf()->addSubObject(object, name);
    }

  private: // singleton
    static Context* getSelf();
    Context() {path = ""; name = ""};
    ~Context();
  };
};

#endif
