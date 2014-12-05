#include <iostream>

#include "syntax/dictionnary.h"

namespace ctvscript {
  namespace parser {

    const std::map<syntax::identifier, syntax::dictionnary_member> syntax::dictionnary({
	{syntax::identifier::whitespace,	{VARIABLE_REGEX("( |\t)+")}},
	  {syntax::identifier::new_line,	{VARIABLE_REGEX("(\r\n|\n)+")}},
	    {syntax::identifier::variable,	{SOLID_REGEX("var")}},
      });

    bool
    syntax::check_in_syntax(cursor& t_cursor, file_end t_end, const dictionnary_member& t_member) {
      if ((size_t)std::distance(t_cursor, t_end) < t_member.m_min_match_size)
	return (false);

      cursor _advance = t_cursor;
      std::advance(_advance, t_member.m_min_match_size);
      std::cerr << "advance:" << t_member.m_min_match_size - 1 << std::endl;
      for (;
	   _advance != t_end && std::regex_match(std::string(t_cursor, _advance), t_member.m_match);
	   ++_advance) std::cerr << std::string(t_cursor, _advance) << " = " << std::regex_match(std::string(t_cursor, _advance), t_member.m_match) << std::endl;
      std::cerr << std::string(t_cursor, _advance) << " = " << std::regex_match(std::string(t_cursor, _advance), t_member.m_match) << std::endl;
      if ((size_t)std::distance(t_cursor, _advance) != t_member.m_min_match_size
	  && std::distance(t_cursor, _advance) > 0) {
	std::cerr << "true" << std::endl;
	t_cursor = _advance;
	return (true);
      }
      return (false);
    }

    const syntax::typed_response
    syntax::get_next_word_type(cursor& t_cursor, file_end t_end) {
      cursor pos = t_cursor;
      for (auto _member : dictionnary) {
	if (check_in_syntax(t_cursor, t_end, _member.second)) {
	  return (std::pair<const syntax::identifier, const std::string>(_member.first, std::string(pos, t_cursor)));
	}
      }
      return (std::make_pair<const syntax::identifier, const std::string>(identifier::unknown, ""));
    }

  };
};
