/*
 * cTV work Loadable
 **/


#ifndef Loadable_H__
# define Loadable_H__

# include <string>
# include <memory>
# include <vector>

# include "error.h"

namespace cTVScript {

  class Surveyor;
  class Loadable;

  /* defined in objectLoadable.hh */
  class ObjectLoadable;
  class Context;

  /* defined in primaryLoadable.hh*/
  template<typename t>
  class primaryAcccessible;
  class stringLoadable;

  /* defined in functionLoadable.hh*/
  class functionLoadable;
  struct parametersPack;

  class Loadable{
  protected:
  public:
    friend class Surveyor;
    friend class Accessor;
    friend class ScriptCallback;
    std::string path;
    std::string name;

  public:
    const std::string&		getName() const { return (name); }
    virtual void		updatePath(const std::string& pathFrom,
					   const std::string& separator = ".") {
      path = pathFrom + separator + name;
    }

  public:
    Loadable(const std::string& _n) : name(_n), _t(0) {}
    virtual ~Loadable() {}

  private:
    typedef unsigned int priority;
    priority _t;
  protected:
    void		registerPriority(priority t) { _t = t; }
  public:
    priority		getPriority() const { return (_t); }

  public:
    virtual const std::string getAsString() const = 0;
 
    virtual bool operator==(const Loadable&) const	{throw cTVScript::InvalidAction("==",	this->name);}
    virtual bool operator< (const Loadable&) const	{throw cTVScript::InvalidAction("<",	this->name);}
    virtual bool operator> (const Loadable&) const	{throw cTVScript::InvalidAction(">",	this->name);}
    virtual bool operator>=(const Loadable&) const	{throw cTVScript::InvalidAction(">=",	this->name);}
    virtual bool operator<=(const Loadable&) const	{throw cTVScript::InvalidAction("<=",	this->name);}

    virtual Loadable* operator=(const Loadable&)	{throw cTVScript::InvalidAction("=",	this->name);}

    virtual Loadable* operator+(const Loadable&) const	{throw cTVScript::InvalidAction("+",	this->name);}
    virtual Loadable* operator*(const Loadable&) const	{throw cTVScript::InvalidAction("*",	this->name);}

    virtual Loadable* operator-(const Loadable&) const	{throw cTVScript::InvalidAction("-",	this->name);}
    virtual Loadable* invertSub(const Loadable&) const	{throw cTVScript::InvalidAction("/",	this->name);}
    virtual Loadable* operator/(const Loadable&) const	{throw cTVScript::InvalidAction("/",	this->name);}
    virtual Loadable* invertDiv(const Loadable&) const	{throw cTVScript::InvalidAction("/",	this->name);}
    virtual Loadable* operator%(const Loadable&) const	{throw cTVScript::InvalidAction("%",	this->name);}
    virtual Loadable* invertMod(const Loadable&) const	{throw cTVScript::InvalidAction("%",	this->name);}

    virtual Loadable* operator[](const std::string&)	{throw cTVScript::InvalidAction("[]",	this->name);}

    virtual void      operator()(parametersPack&)	{throw cTVScript::InvalidAction("()",	this->name);}
  };
};

#endif
