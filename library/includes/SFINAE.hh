#ifndef loadableSFINAE_h__
# define loadableSFINAE_h__

#include "Loadable.hh"

namespace cTVScript{
  namespace SFINAE{

    typedef char one;
    typedef short two;

    template<typename object>
    struct is_Loadable{
      template <typename UpObject>
      static decltype(std::declval<Loadable*&>() = std::declval<UpObject>(), one())
	test(int);
  
      template<typename>
      static two test(...);
  
    public:
      static constexpr bool value = sizeof(test<object>(0)) == sizeof(one);
    };

  };
};


#endif
