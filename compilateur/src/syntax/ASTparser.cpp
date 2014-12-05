#include <iostream>

#include "syntax/ASTparser.h"
#include "syntax/dictionnary.h"
namespace ctvscript {
  namespace parser {

    std::list<AST::node> ASTparser::parse(const std::string& t_file) {
      cursor_data	_cursor(t_file.cbegin(), 0, 0);
      syntax::file_end	_end = t_file.cend();
      std::list<AST::node> _list;

      while (_cursor != _end) {
	cursor_data _save(_cursor);
	syntax::typed_response _identifier = syntax::get_next_word_type((syntax::cursor&)_cursor, _end);

	_cursor.m_line += _save.distance(_cursor);

	std::cout << std::string( (std::string::const_iterator&)_save, (std::string::const_iterator&)_cursor);
	switch (_identifier.first) {
	case syntax::identifier::whitespace:
	  break; //ignore
	case syntax::identifier::new_line:
	  _cursor.m_line += 1, _cursor.m_column = 0;
	  break;
	case syntax::identifier::unknown:
	  /* throw an error*/
	  std::cout << "unknown" << std::endl;
	  break;
	default:
	  /* create node */
	  break;
	}
	_save = _cursor;

	while (syntax::next_word_is<syntax::identifier::whitespace>(_cursor.m_cursor, _end));
	std::cout << std::string( (std::string::const_iterator&)_save, (std::string::const_iterator&)_cursor);
	_cursor.m_line += _save.distance(_cursor);
      }
      std::cout << std::endl;
      return (_list);
    }

  };
};
