#ifndef HELPER_H__
# define HELPER_H__

namespace cTVScript {
  namespace Helper {

    template<unsigned int>
    struct from;

    template<>
    struct from<0> {
      template<typename type>
      type string(const std::string& s) {return (std::stold(s));}
    };

    template<>
    struct from<1> {
      template<typename type>
      type string(const std::string& s) {return (std::stoull(s));}
    };

    template<>
    struct from<2> {
      template<typename type>
      type string(const std::string& s) {return (std::stoll(s));}
    };

    template<typename type>
    arg FromString(const std::string& s) {
      return (from<0
	    + (!std::is_floating_point<type>::value ?
	       (std::is_signed<type>::value == true) : (0))
	      + (std::is_integral<type>::value == true)>::string<type>(s));
    }


    
    template<typename type>
    struct TypePriorityFor{
      static unsigned int get() {
	return (0
		+ (!std::is_floating_point<type>::value ?
		   (std::is_signed<type>::value == true) : (0))
		+ (std::is_integral<type>::value == true)
		+ (std::is_pointer<type>::value  == false)
		);
      }
    };

  };
};

#endif
