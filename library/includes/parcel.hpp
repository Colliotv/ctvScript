#ifndef Parcel_H__
# define PARCEL_H__

#include "accessor.hh"

namespace cTVScript {

  class Parcel{
  private:
    Accessible*	returnValue; // * not really ok
    Accessible* callerObject; // * ok
    ObjectAccessible* parameters; // * really?
  public:
    template<typename thisType>
    static thisType getThis(Parcel&) throw (cTVScript::BadArgue,
					    cTVScript::unspecifiedArgument){
      if (Parcel.callerObject == NULL)
	throw cTVScript::unspecifiedArgument;
      SpecifiedObjectAccessible<thisType>* thisContainer =
	dynamic_cast< SpecifiedObjectAccessible< thisType >* >();
      if (thisContainer == NULL)
	throw cTVScript::BadArgue;
      return (thisContainer->get());
    }

  private:
    template<typename arg*>
    static void loadFromAccessible(Accessible& a, arg*& Argument) {
      specifiedObjectAccessible<arg> *object =
	dynamic_cast< specifiedObjectAccessible< arg > >(a);
      if (object == NULL)
	throw cTVScript::BadArgue.setVarName(a.name);
      Argument = object.get();
    }
    template<typename arg>
    static void LoadFromAccessible(Accessible&a, arg& Argument) {
      integerAccessible<arg>* object =
	dynamic_cast< integerAccessible< arg >* >(a);
      if (object == NULL)
	throw cTVScript::BadArgue.setVarName(a.name);
      Argument = object.get();
    }
    template<>
    static void loadFromAccessible(Accessible& a, ObjectAccessible*& Argument) {
      Argument = dynamic_cast< ObjectAccessible* >(a);
      if (Argument == NULL)
	throw cTVScript::BadArgue.setVarName(a.name);
    }
    template<>
    static void LoadFromAccessible(Accessible& a, std::string& Argument) {
      stringAccessible* string =
	dynamic_cast<stringAccessible*>(a);
      if (object == NULL)
	throw cTVScript::BadArgue.setVarName(a.name);
      Argument = object.get();      
    }

    template< int N >
    static void getArguments(Parcel&) {}
    template<  int N, typename arg, typename... args >
    static void getArguments(Parcel& p, arg& a1, args... a2) throw (cTVScript::BadArgue,
								   cTVScript::unspecifiedArgument){

      if ((*(p.parameters))[N] == NULL)
	throw cTVScript::unspecifiedArgument;

      loadFromAccessible((*p.parameters)[N], a1);

      getArguments<N + 1>(p, a2);
    }
  public:
    template< typename... args >
    static void getArguments(Parcel& p, args... a1) {
      getArguments<0>(p, a1);
    }

  public:
    template<typename returnType>
    static void	setReturn();// todo create for each type

  }; // should be really here?

};
#endif
