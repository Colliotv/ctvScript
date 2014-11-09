#ifndef Instruction_h__
# define Instruction_h__

namespace ctvscript {
  namespace architecture {
    namespace registers {
      class eax {};
    };

    class operations {
    public:
      enum class types : unsigned char {
	_default = 0
	  , parenthesis_open, parenthesis_close
	  , new_operator
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
