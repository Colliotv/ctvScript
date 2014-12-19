#ifndef Derived_Types_h__
# define Derived_Types_h__

#include "data/types.h"

namespace ctvscript {
  namespace byte_code {
    namespace data {
      class derived_types{
      public:
	class const_;
	class reference_;
	class pointeur_;
	class array_;
	class functor_;
      };
    };
  };
};

#endif
