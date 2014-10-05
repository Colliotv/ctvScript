#ifndef Unpacker_H__
# define Unpacker_H__

#include "error.h"

#include "objectLoadable.hh"
#include "primaryLoadable.hh"

namespace cTVScript{
  namespace Converter{
    template <typename arg>
    struct convertLoadableTo;

    template <typename arg>
    struct convertLoadableTo{ // int, double...etc
      static arg transform(Loadable* l) {
	primaryLoadable<arg>* _l =
	  dynamic_cast< primaryLoadable<arg>* >(l);
	if (!_l)
	  throw;
	return (_l->get());
      }
    };

    template <typename arg>
    struct convertLoadableTo<arg&>{ // int&, double&...etc
      static arg& transform(Loadable* l) {
	primaryLoadable<arg>* _l =
	  dynamic_cast< primaryLoadable<arg>* >(l);
	if (!_l)
	  throw;
	return (_l->getRef());
      }
    };

    template <typename arg>
    struct convertLoadableTo<arg*>{ // object*
      static arg* transform(Loadable* l) {
	arg* _l =
	  dynamic_cast< arg* >(l);
	if (!_l)
	  throw;
	return (_l->get());
      }
    };

    template <>
    struct convertLoadableTo<std::string>{ // std::string
      static std::string transform(Loadable* l) {
	StringLoadable* _l =
	  dynamic_cast< StringLoadable* >(l);
	if (!_l)
	  throw;
	return (_l->get());
      }
    };

    template <>
    struct convertLoadableTo<std::string&>{ // std::string&
      static std::string& transform(Loadable* l) {
	StringLoadable* _l =
	  dynamic_cast< StringLoadable* >(l);
	if (!_l)
	  throw;
	return (_l->getRef());
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
      static ReturnType applyFunc(std::vector<Loadable*> parameters, ReturnType (*fn)(Arguments...), final&&... args) {
	return (unfolder<N - 1>::applyFunc
		(parameters, fn,
		 Converter::convertLoadableTo< typename parametersType<N - 1, Arguments...>::type >
		 ::transform(parameters[N-1]),
		 args...));
      }
    };

    template<>
    struct unfolder<0>{
      template <typename ReturnType, typename ...Arguments, typename ...final>
      static ReturnType applyFunc(std::vector<Loadable*> parameters, ReturnType (*fn)(Arguments...), final&&... args) {
	return (fn( args... ));
      }
    };

    template <typename ReturnType, typename ...Arguments>
    ReturnType applyFunction(std::vector<Loadable*> args, ReturnType (*fn)(Arguments...)) {
      return (unfolder<sizeof...(Arguments)>::applyFunc(args, fn));
    }

  };
};

#endif
