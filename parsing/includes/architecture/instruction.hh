#ifndef Instruction_h__
# define Instruction_h__

#include <string>

#include "parsing/parse_string.hh"

namespace cTVScript{
  namespace parsing {

    class parse_string;

    namespace architecture {

      class types;
      class symbol;

    };


    namespace instructions{
      enum class types {
	move, //move from context1 to context 2
      };

      class interface  : public parsingImpl {};

      template<types>
      class instruction : public interface {

      public:
	/*
	  @param the rest of the scripted symbol
	  @return substitute it's part of the scrypted symbol
	 */
	std::string parse_string(std::string line_left);

      };

      class factory{

      private:
      public:
	template<types _t>
	interface* instantiate() { return new instruction<_t>(); }

      private:// singleton
	factory();
      };
    };

  };
};

#endif
