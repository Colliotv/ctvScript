#ifndef Unpacker_H__
# define Unpacker_H__

#include <vector>
#include <string>

#include "error.h"

#include "helper/helper.hh"
#include "helper/sfinae.hh"

#include "loadable.h"

namespace cTVScript{
  namespace Converter{
    template <typename arg>
    struct convertLoadableTo;

    template <typename arg>
    struct convertLoadableTo{ // int, double...etc
      static arg transform(loadable::Loadable* l) {
	loadable::arithmetic<arg>* _l =
	  dynamic_cast< loadable::arithmetic<arg>* >(l);
	if (!_l) {
	  try { return (Helper::FromString<arg>(l->getAsString())); }
	  catch (std::invalid_argument) { throw cTVScript::InvalidParameter(Helper::getTypeName<arg>(), l->getName()); }
	  catch (std::out_of_range) { throw cTVScript::InvalidParameter(Helper::getTypeName<arg>(), l->getName()); }
	}
	return (_l->getLockedValue());
      }
    };

    template <typename arg>
    struct convertLoadableTo<arg&>{ // int&, double&...etc
      static arg& transform(loadable::Loadable* l) {
	loadable::arithmetic<arg>* _l =
	  dynamic_cast< loadable::arithmetic<arg>* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<arg&>(), l->getName());
	return (_l->unlock());
      }
    };

    template<typename arg, bool a>
    struct partObj;

    template<typename arg>
    struct partObj<arg, true>{// object*
      static arg* specT(loadable::Loadable* l) {
	arg* _l = dynamic_cast<arg*>(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<arg*>(), l->getName());
	return (_l);
      }
    };

    template<typename arg> // primary[]
    struct partObj<arg, false> {
      static arg* specT( loadable::Loadable* l) {
	auto _l =
	  dynamic_cast< loadable::array< arg >* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<arg*>(), l->getName());
	return (_l->unlock());
      }
    };

    template <typename arg>
    struct convertLoadableTo< arg* >{ // object* || primary[]
      static arg* transform(loadable::Loadable* l) {
	return (partObj<arg, SFINAE::is_Loadable<arg>::value>::specT(l));
      }
    };

    template <>
    struct convertLoadableTo<std::string>{ // std::string
      static std::string transform(loadable::Loadable* l) {
	loadable::string* _l =
	  dynamic_cast< loadable::string* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<std::string>(), l->getName());
	return (_l->getLockedValue());
      }
    };

    template <>
    struct convertLoadableTo<std::string&>{ // std::string&
      static std::string& transform( loadable::Loadable* l) {
	loadable::string* _l =
	  dynamic_cast< loadable::string* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<std::string&>(), l->getName());
	return (_l->unlock());
      }
    };

  };

  namespace Unpacker{

    /* -------------------------- */
    template <int N, typename... T>
    struct parametersType;

    template <typename T0, typename... T>
    struct parametersType<0, T0, T...> {
      typedef T0 type;
    };

    template <int N, typename T0, typename... T>
    struct parametersType<N, T0, T...> {
      typedef typename parametersType<N-1, T...>::type type;
    };

    
    /* -------------------------- */
    template<unsigned int N>
    struct unfolder;

    template<unsigned int N>
    struct unfolder{
      template <typename ReturnType, typename... Arguments, typename ...final>
      static ReturnType applyFunc(std::vector<loadable::Loadable*> parameters,
				  ReturnType (*fn)(Arguments...),
				  final&&... args) {
	return (unfolder<N - 1>::applyFunc
		(parameters, fn,
		 Converter::convertLoadableTo< typename parametersType<N - 1, Arguments...>::type >
		 ::transform(parameters[N-1]),
		 args...));
      }

      template <typename ReturnType, typename Object, typename... Arguments, typename ...final>
      static ReturnType applyMethode(std::vector<loadable::Loadable*> parameters,
				     Object*	_this,
				     ReturnType (Object::*fn)(Arguments...),
				     final&&... args) {
	return (unfolder<N - 1>::applyMethode
		(parameters, _this, fn,
		 Converter::convertLoadableTo< typename parametersType<N - 1, Arguments...>::type >
		 ::transform(parameters[N-1]),
		 args...));
      }
    };

    template<>
    struct unfolder<0>{
      template <typename ReturnType, typename ...Arguments, typename ...final>
      static ReturnType applyFunc(std::vector<loadable::Loadable*>,
				  ReturnType (*fn)(Arguments...),
				  final&&... args) {
	return (fn( args... ));
      }

      template <typename ReturnType, typename Object, typename ...Arguments, typename ...final>
      static ReturnType applyMethode(std::vector<loadable::Loadable*>,
				     Object*	_this,
				     ReturnType (Object::*fn)(Arguments...),
				     final&&... args) {
	return ((_this->*fn)( args... ));
      }
    };


    template <typename ReturnType, typename ...Arguments>
    ReturnType applyFunction(std::vector<loadable::Loadable*> args,
			     ReturnType (*fn)(Arguments...)) {
      return (unfolder<sizeof...(Arguments)>::applyFunc(args, fn));
    }

    template <typename Object, typename ReturnType, typename ...Arguments>
    ReturnType applyMethode(std::vector<loadable::Loadable*> args,
			    Object* _this,
			    ReturnType (Object::*fn)(Arguments...)) {
      return (unfolder<sizeof...(Arguments)>::applyMethode(args, _this, fn));
    }

  };
};

#endif
