#include <iostream>

#include "syntax/ASTparser.hh"
#include "syntax/dictionnary.hh"

#include "exception/syntax.hh"

namespace ctvscript {
  namespace parser {

    void ASTparser::parse(const std::string& t_file, std::list<AST::node*>& _list) {
      cursor_data	_cursor(t_file.cbegin(), 0, 0);
      syntax::file_end	_end = t_file.cend();

      while (_cursor != _end) {
	cursor_data _save(_cursor);
	syntax::typed_response _identifier = syntax::get_next_word_type((syntax::cursor&)_cursor, _end);

	_cursor.m_column += _save.distance(_cursor);

	switch (_identifier.first) {
	case syntax::identifier::whitespace:
	  break; //ignore
	case syntax::identifier::new_line:
	  _cursor.m_line += 1, _cursor.m_column = 0;
	  break;
	case syntax::identifier::unknown:
	  throw exception::syntax::identification_error(utils::cursor_indicator(_save.m_line, _save.m_column),
							utils::seize_line((syntax::cursor&)_cursor, t_file));
	  break;
	default:
	  std::string _syntax((syntax::cursor&)_save, (syntax::cursor&)_cursor);
	  AST::node* new_node = AST::factory::create_node_by_syntax(_identifier.first, _syntax,
								    AST::node::syntax(utils::seize_line((syntax::cursor&)_cursor,
													t_file), 
										      _save.m_column, _save.m_line));
	  if (new_node == nullptr)
	    throw exception::syntax::identification_error(utils::cursor_indicator(_save.m_line, _save.m_column),
							  utils::seize_line((syntax::cursor&)_cursor, t_file));
	  _list.push_back(new_node);
	  std::cerr << "for syntax::identifier("<< static_cast<int>(_identifier.first)
		    <<") and _syntax( "<< _syntax
		    <<" ): factory recognized it (== NOT TODO)" << std::endl;
	  break;
	}
	_save = _cursor;
      }
    }

  };
};
