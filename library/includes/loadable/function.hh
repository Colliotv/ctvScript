#ifndef FunctionsAccessible_H__
# define FunctionsAccessible_H__

#include <vector>

#include "error.h"

#include "helper/sfinae.hh"
#include "helper/unpacker.hh"
#include "helper/deduce.hh"

#include "loadable/loadable.hh"

namespace cTVScript {

  struct parametersPack{
    loadable::Loadable*			_this;
    loadable::Loadable*&		_return;
    std::vector<loadable::Loadable*>	_arguments;
  };

  namespace loadable {

    class abstractFunction : public Loadable{

    public:
      NEGATE_VALUE_GETTER();
      virtual void call(cTVScript::parametersPack& pack) = 0;
      virtual void operator()(cTVScript::parametersPack& pack) {
	call(pack);
      }

    public:
      abstractFunction(const std::string& name)
	: Loadable(name) {}
      virtual ~abstractFunction() {}

    };

    template <typename Return, typename... Arguments>
    class function : public abstractFunction{
    private:
      Return (*fn)(Arguments...);
    public:
      virtual void call(cTVScript::parametersPack& pack) {
	if (pack._arguments.size() < sizeof...(Arguments))
	  throw cTVScript::exception::MissingParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);
	else
	  throw cTVScript::exception::TooManyParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);

	pack._return = new typename Helper::DeduceLoadableType<Return>::type ("return",
									      Unpacker::applyFunction(pack._arguments, fn));
      }
      function(const std::string& name,
			     Return (*_fn)(Arguments...))
	: abstractFunction(name), fn(_fn){}
    };

    template <typename Return, typename... Arguments>
    class function<Return*, Arguments...> : public abstractFunction{
    private:
      Return (*fn)(Arguments...);
    public:
      virtual void call(cTVScript::parametersPack& pack) {
	if (pack._arguments.size() < sizeof...(Arguments))
	  throw cTVScript::exception::MissingParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);
	else
	  throw cTVScript::exception::TooManyParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);

	pack._return = dynamic_cast<Loadable*> (Unpacker::applyFunction(pack._arguments, fn));
      }
      function(const std::string& name,
			     Return* (*_fn)(Arguments...))
	: abstractFunction(name), fn(_fn){}
    };

    template <typename... Arguments>
    class function<void, Arguments...> : public abstractFunction{
    private:
      void (*fn)(Arguments...);
    public:
      virtual void call(cTVScript::parametersPack& pack) {
	if (pack._arguments.size() < sizeof...(Arguments))
	  throw cTVScript::exception::MissingParameters(Helper::getTypeName<void (*)(Arguments...)>(), this->name);
	else
	  throw cTVScript::exception::TooManyParameters(Helper::getTypeName<void (*)(Arguments...)>(), this->name);
	Unpacker::applyFunction(pack._arguments, fn);
      }
      function(const std::string& name,
			     void (*_fn)(Arguments...))
	: abstractFunction(name), fn(_fn){}
    };

    template <typename Object, typename Return, typename... Arguments>
    class methode : public abstractFunction {
    private:
      Return (Object::*fn)(Arguments...);
    public:
      virtual void call(cTVScript::parametersPack& pack) {
	if (pack._arguments.size() < sizeof...(Arguments))
	  throw cTVScript::exception::MissingParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
	else
	  throw cTVScript::exception::TooManyParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
	Object* _this = dynamic_cast<Object*> (pack._this);
	pack._return = new typename Helper::DeduceLoadableType<Return>::type ("return",
									      Unpacker::applyMethode(pack._arguments, _this, fn));
      }
      methode(const std::string& name, Return (Object::*_fn)(Arguments...))
	: abstractFunction(name), fn(_fn){}
    };

    template <typename Object, typename Return, typename... Arguments>
    class methode<Object, Return*, Arguments...> : public abstractFunction {
    private:
      Return (Object::*fn)(Arguments...);
    public:
      virtual void call(cTVScript::parametersPack& pack) {
	if (pack._arguments.size() < sizeof...(Arguments))
	  throw cTVScript::exception::MissingParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
	else
	  throw cTVScript::exception::TooManyParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
	Object* _this = dynamic_cast<Object*> (pack._this);
	pack._return = dynamic_cast<Loadable*> (Unpacker::applyMethode(pack._arguments, _this, fn));
      }
      methode(const std::string& name, Return* (Object::*_fn)(Arguments...))
	: abstractFunction(name), fn(_fn){}
    };

    template <typename Object, typename... Arguments>
    class methode<Object, void, Arguments...> : public abstractFunction{
    private:
      void (Object::*fn)(Arguments...);
    public:
      virtual void call(cTVScript::parametersPack& pack) {
	if (pack._arguments.size() < sizeof...(Arguments))
	  throw cTVScript::exception::MissingParameters(Helper::getTypeName<void (Object::*)(Arguments...)>(), this->name);
	else
	  throw cTVScript::exception::TooManyParameters(Helper::getTypeName<void (Object::*)(Arguments...)>(), this->name);
	Object* _this = dynamic_cast<Object*> (pack._this);
	Unpacker::applyMethode(pack._arguments, _this, fn);
      }
      methode(const std::string& name, void (Object::*_fn)(Arguments...))
	: abstractFunction(name), fn(_fn){}
    };



    template<bool> struct makemethode{};

    template<>
    struct makemethode<true>{
      template<typename Return, typename Object, typename... Arguments>
      static Loadable* get(const std::string& name, Return (Object::*m)(Arguments...)) {
	return new methode<Object, Return, Arguments...>(name, m);
      }
    };

    template<>
    struct makemethode<false>{
      template<typename Return, typename Object, typename... Arguments>
      static Loadable* get(const std::string&, Return (Object::*)(Arguments...)) {
	static_assert(SFINAE::is_Loadable<Object*>::value == true, "[cTVScript error] Loadable Methode class have to herite from Loadable");
	return NULL;
      }
    };

    template<typename Return, typename Object, typename... Arguments>
    Loadable* loadMethode(const std::string& name, Return (Object::*m)(Arguments...)) {
      return makemethode<SFINAE::is_Loadable<Object*>::value >::get(name, m);
    }

    template<typename Return, typename... Arguments>
    Loadable* loadFunction(const std::string& name, Return (*m)(Arguments...)) {
      return new function<Return, Arguments...>(name, m);
    }

  };
};

#endif
