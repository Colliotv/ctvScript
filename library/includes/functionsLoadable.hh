#ifndef FunctionsAccessible_H__
# define FunctionsAccessible_H__

#include <vector>

#include "error.h"
#include "unpacker.hh"

namespace cTVScript {

  namespace Helper {

    TODO("find a work-around in order to make & returnable")
    template<typename _type>
    struct DeduceLoadableType;

    template<typename _type>
    struct DeduceLoadableType {
      static const bool isConstructible = true;
      typedef primaryLoadable<_type> type;
    };

    template<typename _type>
    struct DeduceLoadableType<_type&> {
      static const bool isConstructible = false;
      //here is the error
    };

    template<>
    struct DeduceLoadableType<std::string> {
      static const bool isConstructible = false;
      typedef stringLoadable type;
    };

    template<>
    struct DeduceLoadableType<std::string&> {
      static const bool isConstructible = false;
      //here is the error
    };
  };


  struct parametersPack{
    Loadable*			_this;
    Loadable*&			_return;
    std::vector<Loadable*>	_arguments;
  };

  class functionLoadable : public Loadable{
  public:
    virtual void call(parametersPack& pack) = 0;

  public:
    functionLoadable(const std::string& name)
      : Loadable(name) {}
  };

  template <typename Return, typename... Arguments>
  class StaticLoadableFunction : public functionLoadable{
  private:
    Return (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      if (pack._arguments.size() < sizeof...(Arguments))
	throw cTVScript::MissingParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);
      else
	throw cTVScript::TooManyParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);

      DestructibleKey key = Key::create();
      pack._return = new typename Helper::DeduceLoadableType<Return>::type ("return",
									    Unpacker::applyFunction(key, pack._arguments, fn));
    }
    StaticLoadableFunction(const std::string& name,
			   Return (*_fn)(Arguments...))
      : functionLoadable(name), fn(_fn){}
  };

  template <typename Return, typename... Arguments>
  class StaticLoadableFunction<Return*, Arguments...> : public functionLoadable{
  private:
    Return (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      if (pack._arguments.size() < sizeof...(Arguments))
	throw cTVScript::MissingParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);
      else
	throw cTVScript::TooManyParameters(Helper::getTypeName<Return (*)(Arguments...)>(), this->name);

      DestructibleKey key = Key::create();
      pack._return = dynamic_cast<Loadable*> (Unpacker::applyFunction(key, pack._arguments, fn));
    }
    StaticLoadableFunction(const std::string& name,
			   Return (*_fn)(Arguments...))
      : functionLoadable(name), fn(_fn){}
  };

  template <typename... Arguments>
  class StaticLoadableFunction<void, Arguments...> : public functionLoadable{
  private:
    void (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      if (pack._arguments.size() < sizeof...(Arguments))
	throw cTVScript::MissingParameters(Helper::getTypeName<void (*)(Arguments...)>(), this->name);
      else
	throw cTVScript::TooManyParameters(Helper::getTypeName<void (*)(Arguments...)>(), this->name);
      Unpacker::applyFunction(pack._arguments, fn);
    }
    StaticLoadableFunction(const std::string& name,
			   void (*_fn)(Arguments...))
      : functionLoadable(name), fn(_fn){}
  };

  template <typename Object, typename Return, typename... Arguments>
  class LoadableMethode : public functionLoadable {
  private:
    Return (Object::*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      if (pack._arguments.size() < sizeof...(Arguments))
	throw cTVScript::MissingParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
      else
	throw cTVScript::TooManyParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
      Object* _this = dynamic_cast<Object*> (pack._this);
      pack._return = new typename Helper::DeduceLoadableType<Return>::type ("return",
									    Unpacker::applyMethode(pack._arguments, _this, fn));
    }
    LoadableMethode(Return (Object::*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename Object, typename Return, typename... Arguments>
  class LoadableMethode<Object, Return*, Arguments...> : public functionLoadable {
  private:
    Return (Object::*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      if (pack._arguments.size() < sizeof...(Arguments))
	throw cTVScript::MissingParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
      else
	throw cTVScript::TooManyParameters(Helper::getTypeName<Return (Object::*)(Arguments...)>(), this->name);
      Object* _this = dynamic_cast<Object*> (pack._this);
      pack._return = dynamic_cast<Loadable*> (Unpacker::applyMethode(pack._arguments, _this, fn));
    }
    LoadableMethode(Return (Object::*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename Object, typename... Arguments>
  class LoadableMethode<Object, void, Arguments...> : public functionLoadable{
  private:
    void (Object::*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      if (pack._arguments.size() < sizeof...(Arguments))
	throw cTVScript::MissingParameters(Helper::getTypeName<void (Object::*)(Arguments...)>(), this->name);
      else
	throw cTVScript::TooManyParameters(Helper::getTypeName<void (Object::*)(Arguments...)>(), this->name);
      Object* _this = dynamic_cast<Object*> (pack._this);
      Unpacker::applyMethode(pack._arguments, _this, fn);
    }
    LoadableMethode(void (Object::*_fn)(Arguments...)) : fn(_fn){}
  };

};

#endif
