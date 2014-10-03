#include <iostream>
#include <vector>
#include <tuple>

/*
* Non-Typed Part
*/
class Loadable{
public:
  virtual std::string getAsString() { return ""; }
};

struct parametersPack{
public:
  Loadable* returnValue;
  std::vector<Loadable*> arguments;
};

class StringLoadable : public Loadable{
private:
  std::string value;
public:
  StringLoadable(std::string _s) : value(_s) {}
  virtual std::string getAsString() { return value; }
  virtual std::string get() { return value; }
  virtual std::string& getRef() { return value; }
};

template<typename type>
class primaryLoadable : public Loadable{
private:
  type value;
public:
  primaryLoadable(type _v) : value(_v) {}
  virtual std::string getAsString() { return std::to_string(value); }
  type get() {return value;}
  type& getRef() {return value;}
};

class functionLoadable : public Loadable{
public:
  virtual void call(parametersPack& pack) = 0;
};


namespace Unpacker{
  /*
  * Treat For Each Type
  */
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

  template <>
  struct convertLoadableTo<std::string>{ // int&, double&...etc
    static std::string transform(Loadable* l) {
      StringLoadable* _l =
	dynamic_cast< StringLoadable* >(l);
      if (!_l)
	throw;
      return (_l->get());
    }
  };

  template <>
  struct convertLoadableTo<std::string&>{ // int&, double&...etc
    static std::string& transform(Loadable* l) {
      StringLoadable* _l =
	dynamic_cast< StringLoadable* >(l);
      if (!_l)
	throw;
      return (_l->getRef());
    }
  };

  /*
  * Getting Parameters type N in variadic Templates
  */
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

	

  /*
  * Unpacking all arguments
  */
  template<unsigned int N>
  struct helper;

  template<unsigned int N>
  struct helper{
    template <typename ReturnType, typename... Arguments, typename ...final>
    static ReturnType applyFunc(std::vector<Loadable*> parameters, ReturnType (*fn)(Arguments...), final&&... args) {
      return (helper<N - 1>::applyFunc
	      (parameters, fn,
	       convertLoadableTo< typename parametersType<N - 1, Arguments...>::type >
	       ::transform(parameters[N-1]),
	       args...));
    }
  };

  template<>
  struct helper<0>{
    template <typename ReturnType, typename ...Arguments, typename ...final>
    static ReturnType applyFunc(std::vector<Loadable*> parameters, ReturnType (*fn)(Arguments...), final&&... args) {
      return (fn( args... ));
    }
  };

  template <typename ReturnType, typename ...Arguments>
  ReturnType applyFunc(std::vector<Loadable*> args, ReturnType (*fn)(Arguments...)) {
    return (helper<sizeof...(Arguments)>::applyFunc(args, fn));
  }

};// namespace Unpacker


/*
* Static Loadable Function
*/
template <typename Return, typename... Arguments>
class StaticLoadableFunction : public functionLoadable{
private:
  Return (*fn)(Arguments...);
public:
  Return calling(Arguments... args) {
    Return value = fn(args...);
    return (value);
  }
  virtual void call(parametersPack& pack) {
    Unpacker::applyFunc(pack.arguments, fn);
  }
  StaticLoadableFunction(Return (*_fn)(Arguments...)) : fn(_fn){}
};

template <typename... Arguments>
class StaticLoadableFunction<void, Arguments...> : public functionLoadable{
private:
  void (*fn)(Arguments...);
public:
  void calling(Arguments... args) {
    fn(args...);
  }
  virtual void call(parametersPack& pack) {
    
  }
  StaticLoadableFunction(void (*_fn)(Arguments...)) : fn(_fn){}
};




/* here is the sample function */
int function(int& a, int& b) {
  a = 1;
  b = 5;
  return (a + b);
}

void function2(int, int) {
}

/* main test */
int main() {
  StringLoadable	s("toto");
  primaryLoadable<int>	a(2);
  primaryLoadable<int>	b(3);
  std::cout << a.getAsString() << std::endl;
  std::cout << b.getAsString() << std::endl;
  std::cout << s.getAsString() << std::endl;

  parametersPack p;
  p.arguments.push_back(&a);
  p.arguments.push_back(&b);

  StaticLoadableFunction<int, int&, int&> f(&function);
  f.call(p);
  std::cout << a.getAsString() << std::endl;
  std::cout << b.getAsString() << std::endl;
  int o = 2;
}
