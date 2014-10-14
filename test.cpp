#include <stdio.h>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
typedef struct{ char t[1]; } one;
typedef struct{ char t[2]; } two;

template<typename probableArray>
struct is_container {
  template<typename _o> struct test2 : std::false_type{};
  template<typename _o> struct test2<_o[]> : std::true_type{};
  template<typename _o> struct test2<_o*> : std::true_type{};

  template<typename _o>
  static one test1(typename _o::iterator*);
  template<typename>
  static two test1(...);

public:
  static constexpr bool value =
    (test2<probableArray>::value)
    || (sizeof(test1<probableArray>(0)) == sizeof(one));
};

    template <typename _Get_TypeName>
    const char* getTypeName()
    {
      static std::string name;

      if (name.empty())
	{
	  const char *beginStr = "_Get_TypeName =";
	  const size_t beginStrLen = 15;
	  size_t begin,length;
	  name = __PRETTY_FUNCTION__;

	  begin = name.find(beginStr) + beginStrLen + 1;
	  length = name.find("]",begin) - begin;
	  name = name.substr(begin,length);
	}

      return name.c_str();
    }


int main() {
  std::cout << getTypeName<int>() << is_container<int>::value << std::endl;
  std::cout << getTypeName<int[]>() << is_container<int[]>::value << std::endl;
  std::cout << getTypeName<int*>() << is_container<int*>::value << std::endl;
  std::cout << getTypeName<std::vector<int> >() << is_container<std::vector<int> >::value << std::endl;

}
