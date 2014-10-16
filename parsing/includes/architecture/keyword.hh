#ifndef keyword_h__
# define keyword_h__

#include <map>

namespace cTVScript {
  namespace parsing {

    namespace instructions {

      class keywords {
      public:
	enum class type : char{
	  conditional,
	    declaration,
	    no_key,
	};
      private:
	static const std::map<const std::string, type> _keywords;

      public:
	static type matchWord(std::string& line) {
	  for (auto word : _keywords) {
	    if (line.find(word.first) == 0) {
	      line = line.substr(word.first.size());
	      return (word.second);
	    }
	  }
	  return (type::no_key);
	};
      private://singleton
      };

      const std::map<const std::string, keywords::type> keywords::_keywords = {
	{"if", type::conditional}
      };

    };

  };
};
#endif
