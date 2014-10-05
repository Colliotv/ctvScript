/*
 * cTV work Accessor
 **/


#ifndef Accessor_H__
# define Accessor_H__

# include <string>

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


  class Loadable{
  protected:
    friend class Surveyor;
    friend class Accessor;
    std::string path;
    std::string name;
  public:
    Loadable(std::string& _n) : name(_n) {}
    virtual ~Loadable();

  private:
    typedef unsigned int type;
    type _t;
  protected:
    void		registerType(type t) { _t = t; }
  public:
    type		getType();

  public:
    virtual const std::string& getAsString() {return "";}
 
    virtual Loadable& operator==(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator&&(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator||(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator<(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator>(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator>=(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator<=(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator=(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator+(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator-(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator*(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator/(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& invertDiv(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator%(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& invertMod(Loadable&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Loadable& operator[](std::string&)	{throw cTVScript::CantAccessSubCHilds(this.name);}
  };

};

#endif
