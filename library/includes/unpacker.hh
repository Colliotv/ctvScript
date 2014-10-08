#ifndef Unpacker_H__
# define Unpacker_H__

#include <vector>
#include <string>

#include "error.h"

#include "helper.hh"

#include "objectLoadable.hh"
#include "primaryLoadable.hh"

namespace cTVScript{
  namespace Converter{
    template <typename arg>
    struct convertLoadableTo;

    template <typename arg>
    struct convertLoadableTo{ // int, double...etc
      static arg transform(std::shared_ptr<Key>, Loadable* l) {
	primaryLoadable<arg>* _l =
	  dynamic_cast< primaryLoadable<arg>* >(l);
	if (!_l) {
	  try { return (Helper::FromString<arg>(l->getAsString())); }
	  catch (std::invalid_argument) { throw cTVScript::InvalidParameter(Helper::getTypeName<arg>(), l->name); }
	  catch (std::out_of_range) { throw cTVScript::InvalidParameter(Helper::getTypeName<arg>(), l->name); }
	}
	return (_l->getLockedValue());
      }
    };

    template <typename arg>
    struct convertLoadableTo<arg&>{ // int&, double&...etc
      static arg& transform(std::shared_ptr<Key> key, Loadable* l) {
	primaryLoadable<arg>* _l =
	  dynamic_cast< primaryLoadable<arg>* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<arg&>(), l->name);
	return (_l->unlock(key));
      }
    };

    template <typename arg>
    struct convertLoadableTo<arg*>{ // object*
      static arg* transform(std::shared_ptr<Key> key, Loadable* l) {
	arg* _l =
	  dynamic_cast< arg* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<arg*>(), l->name);
	return (_l->unlock(key));
      }
    };

    template <>
    struct convertLoadableTo<std::string>{ // std::string
      static std::string transform(std::shared_ptr<Key>, Loadable* l) {
	stringLoadable* _l =
	  dynamic_cast< stringLoadable* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<std::string>(), l->name);
	return (_l->getLockedValue());
      }
    };

    template <>
    struct convertLoadableTo<std::string&>{ // std::string&
      static std::string& transform(std::shared_ptr<Key> key, Loadable* l) {
	stringLoadable* _l =
	  dynamic_cast< stringLoadable* >(l);
	if (!_l)
	  throw cTVScript::InvalidParameter(Helper::getTypeName<std::string&>(), l->name);
	return (_l->unlock(key));
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
      static ReturnType applyFunc(std::shared_ptr<Key> key,
				  std::vector<Loadable*> parameters,
				  ReturnType (*fn)(Arguments...),
				  final&&... args) {
	return (unfolder<N - 1>::applyFunc
		(key, parameters, fn,
		 Converter::convertLoadableTo< typename parametersType<N - 1, Arguments...>::type >
		 ::transform(key, parameters[N-1]),
		 args...));
      }
    };

    template<>
    struct unfolder<0>{
      template <typename ReturnType, typename ...Arguments, typename ...final>
      static ReturnType applyFunc(std::shared_ptr<Key>,
				  std::vector<Loadable*>,
				  ReturnType (*fn)(Arguments...),
				  final&&... args) {
	return (fn( args... ));
      }
    };

    template <typename ReturnType, typename ...Arguments>
    ReturnType applyFunction(std::shared_ptr<Key> key,
			     std::vector<Loadable*> args,
			     ReturnType (*fn)(Arguments...)) {
      return (unfolder<sizeof...(Arguments)>::applyFunc(key, args, fn));
    }


    TODO("finish unpacker")
    template <typename Object, typename ReturnType, typename ...Arguments>
    ReturnType applyMethode(std::shared_ptr<Key> key,
			    std::vector<Loadable*> args,
			    Object* _this,
			    ReturnType (Object::*fn)(Arguments...)) {
      return (unfolder<sizeof...(Arguments)>::applyMethode(key, args, _this, fn));
    }

  };
};

#endif
