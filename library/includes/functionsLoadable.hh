#ifndef FunctionsAccessible_H__
# define FunctionsAccessible_H__

#include <vector>

#include "error.h"
#include "unpacker.hh"

namespace cTVScript {

  struct parametersPack{
    Loadable*			_this;
    Loadable*			_return;
    std::vector<Loadable*>	_arguments;
  };

  class functionLoadable : public Loadable{
  public:
    virtual void call(parametersPack& pack) = 0;
  };

  template <typename Return, typename... Arguments>
  class StaticLoadableFunction : public functionLoadable{
  private:
    Return (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      //create return here
      Unpacker::applyFunction(pack._arguments, fn);
    }
    StaticLoadableFunction(Return (*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename... Arguments>
  class StaticLoadableFunction<void, Arguments...> : public functionLoadable{
  private:
    void (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      Unpacker::applyFunction(pack._arguments, fn);
    }
    StaticLoadableFunction(void (*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename Object, typename Return, typename... Arguments>
  class LoadableMethode : public functionLoadable {
  private:
    Return (Object::*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      //create return here
      //unpack this here
      Unpacker::applyMethode(pack._arguments, fn);
    }
    LoadableMethode(Return (Object::*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename Object, typename... Arguments>
  class LoadableMethode<Object, void, Arguments...> : public functionLoadable{
  private:
    void (Object::*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      //unpack this here
      Unpacker::applyMethode(pack._arguments, fn);
    }
    LoadableMethode(void (Object::*_fn)(Arguments...)) : fn(_fn){}
  };

};

#endif
