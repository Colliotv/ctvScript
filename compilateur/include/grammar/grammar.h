#ifndef Grammar_h__
# define Grammar_h__

# define SOLID_REGEXP(__string__) std::regexp(__string__), sizeof(__string__)

namespace ctvscript {
  class syntax {
  public:
    enum class identifier {
      whitespace, new_line
	, variable
	, function
    };
    struct grammar { std::regexp m_match; size_t m_min_match_size; syntax::identifier m_dientifier; };
    static const std::list<grammar> m_grammar;
  };

  std::list<grammar> m_grammar({
      {"( |\t)*"	, 1, whitespace}
      {"(\n)*"		, 1, new_line}
      ,{SOLID_REGEXP("var"), variable}
      ,{SOLID_REGEXP("fun"), function}
    });
};
#endif
