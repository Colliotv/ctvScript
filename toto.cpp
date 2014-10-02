#include <iostream>
#include <vector>
#include <tuple>

/* here is the sample function */
int function(int a, int b) {
  return (a + b);
}

void function2(int, int) {
}

/* my loadable function */
class Loadable{
public:
  virtual std::string getAsString() { return ""; }
};

template<typename type>
class primaryLoadable : public Loadable{
private:
  type value;
public:
  primaryLoadable(type _v) : value(_v) {}
  virtual std::string getAsString() { return std::to_string(value); }
  type get() {return value;}
};

namespace Unpacker{
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

  template<unsigned int N>
  struct helper{
    template <typename ReturnType, typename ...Arguments, typename ...final>
    static ReturnType applyFunc(std::vector<Loadable*> parameters, ReturnType (*fn)(Arguments...), final... args) {
      helper<N - 1>::applyFunc(parameters, fn, args...,
			       dynamic_cast< primaryLoadable< typename parametersType<N - 1, Arguments...>::type >* >
	(parameters[N - 1])->get());
    }
  };

  template<>
  struct helper<0>{
    template <typename ReturnType, typename ...Arguments, typename ...final>
    static ReturnType applyFunc(std::vector<Loadable*> parameters, ReturnType (*fn)(Arguments...), final... args) {
      fn(args...);
    }
  };

  template <typename ReturnType, typename ...Arguments>
  ReturnType applyFunc(std::vector<Loadable*> args, ReturnType (*fn)(Arguments...)) {
    helper<sizeof...(Arguments)>::applyFunc(args, fn);
  }
};


struct parametersPack{
public:
  Loadable* returnValue;
  std::vector<Loadable*> arguments;
};


class functionLoadable{
public:
  virtual void call(parametersPack& pack) = 0;
};

template <typename Return, typename... Arguments>
class FunctionTest : public functionLoadable{
private:
  Return (*fn)(Arguments...);
public:
  Return calling(Arguments... args) {
    Return value = fn(args...);
    return (value);
  }
  virtual void call(parametersPack& pack) {

  }
  FunctionTest(Return (*_fn)(Arguments...)) : fn(_fn){}
};

template <typename... Arguments>
class FunctionTest<void, Arguments...> : public functionLoadable{
private:
  void (*fn)(Arguments...);
public:
  void calling(Arguments... args) {
    fn(args...);
  }
  virtual void call(parametersPack& pack) {
  }
  FunctionTest(void (*_fn)(Arguments...)) : fn(_fn){}
};

/* main test */
int main() {
  primaryLoadable<int> a(2);
  primaryLoadable<int> b(3);
  std::cout << a.getAsString() << std::endl;
  std::cout << b.getAsString() << std::endl;

  parametersPack p;
  p.arguments.push_back(&a);
  p.arguments.push_back(&b);

  Unpacker::applyFunc(p.arguments, &function);
}
