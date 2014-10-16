#ifndef loadableSFINAE_h__
# define loadableSFINAE_h__

//#include "loadable/loadable.hh"

namespace cTVScript{
  namespace sfinae{

    typedef struct{ char t[1]; } one;
    typedef struct{ char t[2]; } two;

    template<typename object>
    struct is_Loadable{
      template <typename UpObject>
      static decltype(std::declval<loadable::Loadable*&>() = std::declval<UpObject>(), one())
	test(int);
  
      template<typename>
      static two test(...);
  
    public:
      static constexpr bool value = sizeof(test<object>(0)) == sizeof(one);
    };

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

  };
};


#endif
