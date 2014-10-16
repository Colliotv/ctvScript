#ifndef Line_h__
# define Line_h__

#include <string>

#include "parsing/parse_string.hh"

#include "architecture/instruction.hh"

namespace cTVScript {
  namespace parsing {

    class parse_string;

    namespace instructions {

      class line : public parsingImpl {
      public:
	virtual std::string parse_string(std::string symbol_left);

      public:
	line();
	~line();
      };

    };

  };
};

#endif
