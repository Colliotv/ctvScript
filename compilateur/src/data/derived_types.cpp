#include "data/derived_types.h"

namespace ctvscript {
  namespace byte_code {
    namespace data {
      namespace type {
	wrapper	table(type::map({
	      {"int",		{new container::underived(new primary<false, true, 4>())} },
	      {"signed int",	{new container::underived(new primary<false, true, 4>())} },
	      {"unsigned int",	{new container::underived(new primary<false, false, 4>())} },
	      {"double",		{new container::underived(new primary<true, true, 8>())} },
	      { "std", type::map({
		    {"size_t",		{new container::underived(new primary<false, false, 8>())} },
		      }) },
	      }));
      };
    };
  };
};
