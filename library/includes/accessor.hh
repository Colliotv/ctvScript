/*
 * cTV work Accessor
 **/


#ifndef Accessor_H__
# define Accessor_H__

# include "error.h"

namespace cTVScript {

  class Accessor;
  class Surveyor;
  class Accessible;

  /* defined in objectAccessible.hh */
  class ObjectAccessible;
  class Context;

  /* defined in primaryAccessible.hh*/
  template<typename t>
  class primaryAcccessible;
  class stringAccessible;

  class Accessor{
  private:
  };


  class Acessible{
  protected:
    friend class Surveyor;
    friend class Accessor;
    std::string path;
    std::string name;
  public:
    Accessible();
    ~Accessible();

  public: // when operands in sub class;
    enum Type {OBJECT, STRING, FLOATING, INTEGER};
    Accessible::Type	getType();

  public:
    virtual Accessible& operator==(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator&&(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator||(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator<(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator>(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator=<(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator=>(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator=(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator+(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator-(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator*(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator/(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator%(Accessible&)	{throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator+=(Accessible&) {throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator-=(Accessible&) {throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator*=(Accessible&) {throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator/=(Accessible&) {throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator%=(Accessible&) {throw cTVScript::IsAnObject(this.name);}
    virtual Accessible& operator[](std::string&){throw cTVScript::CantAccessSubCHilds(this.name);}
  };

};

#endif
