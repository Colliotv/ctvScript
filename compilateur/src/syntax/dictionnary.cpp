#include <iostream>

#include "syntax/dictionnary.h"

namespace ctvscript {
  namespace parser {

    const std::map< syntax::identifier, std::list<syntax::dictionnary_member> > syntax::composed_dictionnary({
	{syntax::identifier::string_litteral,	{ {SOLID_REGEX("\"")}, {VARIABLE_REGEX("[^\"]*")}, {SOLID_REGEX("\"")} }},
	{syntax::identifier::char_litteral,	{ {SOLID_REGEX("'")}, {VARIABLE_REGEX("[^']")}, {SOLID_REGEX("'")} }},
	{syntax::identifier::floating,		{ {SOLID_REGEX("[[:d:]]*")}, {VARIABLE_REGEX("\\.")}, {SOLID_REGEX("[[:d:]]*")} }},
      });

    const std::map<syntax::identifier, syntax::dictionnary_member> syntax::dictionnary({
	{syntax::identifier::new_line,			{VARIABLE_REGEX("(\r\n|\n)+")}},
	{syntax::identifier::whitespace,		{VARIABLE_REGEX("[[:blank:]]+")}},

	{syntax::identifier::variable,			{SOLID_REGEX("var")}},
	{syntax::identifier::function,			{SOLID_REGEX("def")}},

	{syntax::identifier::if_statement,		{SOLID_REGEX("if")}},
	{syntax::identifier::else_statement,		{SOLID_REGEX("else")}},
	{syntax::identifier::else_statement,		{SOLID_REGEX("else")}},
	{syntax::identifier::return_statement,		{SOLID_REGEX("return")}},

	{syntax::identifier::typedef_statement,		{SOLID_REGEX("typedef")}},

	{syntax::identifier::import_statement,		{SOLID_REGEX("import")}},

	{syntax::identifier::namespace_statement,	{SOLID_REGEX("namespace")}},
	{syntax::identifier::class_statement,		{SOLID_REGEX("class")}},
	{syntax::identifier::public_statement,		{SOLID_REGEX("public")}},
	{syntax::identifier::private_statement,		{SOLID_REGEX("private")}},

	{syntax::identifier::semicolon,			{VARIABLE_REGEX(";+")}},
	{syntax::identifier::Bparenthesis,		{VARIABLE_REGEX("\\(")}},
	{syntax::identifier::Eparenthesis,		{VARIABLE_REGEX("\\)")}},
	{syntax::identifier::Bbrackets,			{VARIABLE_REGEX("\\{")}},
	{syntax::identifier::Ebrackets,			{VARIABLE_REGEX("}")}},
	{syntax::identifier::Bsqbrackets,		{VARIABLE_REGEX("\\[")}},
	{syntax::identifier::Esqbrackets,		{VARIABLE_REGEX("]")}},

	{syntax::identifier::scope_resolution,		{VARIABLE_REGEX("::")}},
	{syntax::identifier::increment,			{VARIABLE_REGEX("\\+\\+")}},
	{syntax::identifier::decrement,			{VARIABLE_REGEX("--")}},

	{syntax::identifier::struct_dereference,	{VARIABLE_REGEX("\\.")}},
	{syntax::identifier::struct_reference,		{VARIABLE_REGEX("->")}},

	{syntax::identifier::colon,			{VARIABLE_REGEX(":")}},
	{syntax::identifier::addition,			{VARIABLE_REGEX("\\+")}},
	{syntax::identifier::substraction,		{VARIABLE_REGEX("-")}},
	{syntax::identifier::division,			{VARIABLE_REGEX("/")}},
	{syntax::identifier::multiplication,		{VARIABLE_REGEX("\\*")}},
	{syntax::identifier::modulo,			{VARIABLE_REGEX("%")}},

	{syntax::identifier::integer,			{VARIABLE_REGEX("([0-9])+(([a-z]|[A-Z])|[0-9])*")}},
	{syntax::identifier::type_id,			{VARIABLE_REGEX("([a-z]|[A-Z])+(([a-z]|[A-Z])|[0-9])*")}},
      });

    bool
    syntax::check_in_syntax(cursor& t_cursor, file_end t_end, const dictionnary_member& t_member) {
      if ((size_t)std::distance(t_cursor, t_end) < t_member.m_min_match_size)
	return (false);

      cursor _advance = t_cursor;
      std::advance(_advance, t_member.m_min_match_size);
      for (;
	   _advance != t_end && std::regex_match(std::string(t_cursor, _advance), t_member.m_match);
	   ++_advance);

      if ((size_t)std::distance(t_cursor, _advance) != t_member.m_min_match_size
	  && std::distance(t_cursor, _advance) > 0) {
	if (_advance != t_end)
	  t_cursor = --_advance;
	else
	  t_cursor = _advance;
	return (true);
      }
      return (false);
    }

    const syntax::typed_response
    syntax::get_next_word_type(cursor& t_cursor, file_end t_end) {
      cursor pos = t_cursor;
      for (auto _member_list : composed_dictionnary) {
	bool is_composed = (_member_list.second.size() > 0);
	for (auto _member : _member_list.second) {
	  if (!check_in_syntax(t_cursor, t_end, _member)) {
	    is_composed = false;
	    break;
	  }
	}
	if (!is_composed)
	  t_cursor = pos;
	else
	  return (std::pair<const syntax::identifier, const std::string>(_member_list.first, std::string(pos, t_cursor)));
      }
      for (auto _member : dictionnary) {
	if (check_in_syntax(t_cursor, t_end, _member.second)) {
	  return (std::pair<const syntax::identifier, const std::string>(_member.first, std::string(pos, t_cursor)));
	}
      }
      return (std::make_pair<const syntax::identifier, const std::string>(identifier::unknown, ""));
    }

  };
};
