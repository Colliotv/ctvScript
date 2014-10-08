/*
 * cTV work Accessor
 **/


#ifndef Accessor_H__
# define Accessor_H__

# include <string>
# include <memory>

# include "error.h"

namespace cTVScript {

  class Accessor;
  class Surveyor;
  class Loadable;

  /* defined in objectLoadable.hh */
  class ObjectLoadable;
  class Context;

  /* defined in primaryLoadable.hh*/
  template<typename t>
  class primaryAcccessible;
  class stringLoadable;

  class Accessor{
  private:
  };


  class Key{
  public:
    static std::shared_ptr<Key> create() { return std::shared_ptr<Key> (new Key()); }
    void	notify(Loadable*) {}

  public:
    ~Key() {} // on destruct avert Accessor
  private:
    Key() {}
  };
  typedef std::shared_ptr<Key> DestructibleKey;

  class Loadable{
  protected:
    friend class Surveyor;
    friend class Accessor;
    std::string path;
    std::string name;
  public:
    Loadable(const std::string& _n) : name(_n) {}
    virtual ~Loadable() {}

  private:
    typedef unsigned int priority;
    priority _t;
  protected:
    void		registerPriority(priority t) { _t = t; }
  public:
    priority		getPriority() { return (_t); }

  public:
    virtual const std::string getAsString() {return "";}
 
    virtual Loadable* operator==(Loadable*)		{throw cTVScript::InvalidAction("==",	this->name);}
    virtual Loadable* operator<(Loadable*)		{throw cTVScript::InvalidAction("<",	this->name);}
    virtual Loadable* operator>(Loadable*)		{throw cTVScript::InvalidAction(">",	this->name);}
    virtual Loadable* operator>=(Loadable*)		{throw cTVScript::InvalidAction(">=",	this->name);}
    virtual Loadable* operator<=(Loadable*)		{throw cTVScript::InvalidAction("<=",	this->name);}
    virtual Loadable* operator=(Loadable*)		{throw cTVScript::InvalidAction("=",	this->name);}
    virtual Loadable* operator+(Loadable*)		{throw cTVScript::InvalidAction("+",	this->name);}
    virtual Loadable* operator-(Loadable*)		{throw cTVScript::InvalidAction("-",	this->name);}
    virtual Loadable* operator*(Loadable*)		{throw cTVScript::InvalidAction("*",	this->name);}
    virtual Loadable* operator/(Loadable*)		{throw cTVScript::InvalidAction("/",	this->name);}
    virtual Loadable* invertDiv(Loadable*)		{throw cTVScript::InvalidAction("/",	this->name);}
    virtual Loadable* operator%(Loadable*)		{throw cTVScript::InvalidAction("%",	this->name);}
    virtual Loadable* invertMod(Loadable*)		{throw cTVScript::InvalidAction("%",	this->name);}
    virtual Loadable* operator[](const std::string&)	{throw cTVScript::InvalidAction("[]",	this->name);}
  };
};

#endif
