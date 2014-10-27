#ifndef Instruction_h__
# define Instruction_h__

namespace ctvscript {
  namespace architecture {

    class instructions {
    public:
      enum class operations_types : unsigned char {
	_default = 0
	  , ternary, logical_or, logical_and
	  , bitwise_or, bitwise_xor, bitwise_and
	  , equality
	  , comparison
	  , addition
	  , shift
	  , multiplication
	  
	  
      };
    };

  };
};

#endif
