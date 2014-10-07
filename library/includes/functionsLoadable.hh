#ifndef FunctionsAccessible_H__
# define FunctionsAccessible_H__

#include "error.hh"
#include "unpacker.hh"

namespace cTVScript {

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
      Unpacker::applyFunction(pack.arguments, fn);
    }
    StaticLoadableFunction(Return (*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename... Arguments>
  class StaticLoadableFunction<void, Arguments...> : public functionLoadable{
  private:
    void (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      Unpacker::applyFunction(pack.arguments, fn);
    }
    StaticLoadableFunction(void (*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename Object, typename Return, typename... Arguments>
  class LoadableMethode : public functionLoadable {
  private:
    Return (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      //create return here
      //unpack this here
      Unpacker::applyMethode(pack.arguments, fn);
    }
    LoadableMethode(Return (*_fn)(Arguments...)) : fn(_fn){}
  };

  template <typename Object, typename... Arguments>
  class LoadableMethode<void, Arguments...> : public functionLoadable{
  private:
    void (*fn)(Arguments...);
  public:
    virtual void call(parametersPack& pack) {
      //unpack this here
      Unpacker::applyMethode(pack.arguments, fn);
    }
    LoadableMethode(void (*_fn)(Arguments...)) : fn(_fn){}
  };

};

#endif
