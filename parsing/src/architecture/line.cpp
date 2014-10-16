#include <regex>
#include <iostream>

#include "architecture/line.hh"
#include "architecture/keyword.hh"

namespace cTVScript {
    namespace parsing {
      namespace instructions {


	/*
	 * instruction line implementation
	 */
	line::line() {}
	line::~line() {}	

	std::string
	line::parse_string(std::string symbol_left) {
	  std::string ret = (symbol_left.find(";") != std::string::npos) ?
	    symbol_left.substr(symbol_left.find(";") + 1) : "";

	  std::string line = (symbol_left.find(";") != std::string::npos) ?
	    symbol_left.substr(0, symbol_left.find(";") + 1) : "";

	  line = line.substr(line.find_first_not_of(" "));

	  switch (keywords::matchWord(line)) {
	  case keywords::type::conditional:
	    /* do something */
	    break;
	  case keywords::type::declaration:
	    /* push implying */
	    /* do op after = (if any )*/
	    /* move implying */
	    break;
	  default:
	    /* do op after = (if any )*/
	    /* move implying */
	    break;
	  }
	  return (line);
	}

      };
    };
};
