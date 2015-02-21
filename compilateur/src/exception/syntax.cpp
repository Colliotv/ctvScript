#include <sstream>

#include "exception/syntax.h"

namespace ctvscript {
  namespace utils {
    /*
     * utils for identification error
     */
    std::string seize_line(const std::string::const_iterator& t_cursor_line, const std::string& t_file) {
      std::string::const_iterator line_beg = t_cursor_line;
      std::string::const_iterator line_end = t_cursor_line;

      if (*t_cursor_line == '\n') {
	std::advance(line_beg, -1);
	std::advance(line_end, -1);
      }

      while (line_beg != t_file.cbegin() && *line_beg != '\n') std::advance(line_beg, -1);
      if (*line_beg == '\n') std::advance(line_beg, 1);

      while (line_end != t_file.cend() && *line_end != '\n') std::advance(line_end, 1);
      if (*line_end == '\n') std::advance(line_end, -1);

      return (std::string(line_beg, line_end));
    }

    cursor_indicator::cursor_indicator(std::size_t t_line, std::size_t t_column)
      : m_line(t_line), m_column(t_column) {}
    cursor_indicator::cursor_indicator(const cursor_indicator& t_cursor)
      : m_line(t_cursor.m_line), m_column(t_cursor.m_column) {}

    std::size_t  cursor_indicator::getLine() const  {  return m_line;  }
    std::size_t cursor_indicator::getColumn() const { return m_column; }
  };

  namespace exception {
    namespace syntax {
      /*
       * syntax error
       */
      error::		error(const std::string& _error) noexcept
	: std::logic_error(_error.c_str()) {}
      error::	~error() noexcept {}
      
      /*
       * identification error
       */
      const std::string identification_error::write_msg(const utils::cursor_indicator& t_cursor, const std::string& t_line) {
	std::stringstream ss;
	ss 
	  <<"at ("<< t_cursor.getLine() <<", "<< t_cursor.getColumn() <<") symbols or formula not recognized by dictionnary:"
	  << std::endl << t_line
	  << std::endl << std::string(t_cursor.getColumn(), ' ') << "^";
	return ss.str();
      }

      identification_error::identification_error(const utils::cursor_indicator& t_cursor, const std::string& t_line) noexcept
	: syntax::error(write_msg(t_cursor, t_line)), m_cursor(t_cursor) {}
      identification_error::~identification_error() noexcept {}

      const utils::cursor_indicator& identification_error::getCursor() const { return m_cursor; }

      /*
       * undefined type
       */
      const std::string	undefined_type::write_msg(const AST::node::syntax& _syntax, const std::string& _name) {
	std::stringstream ss;

	ss
	  << "at (" << _syntax.get_line() << ", " << _syntax.get_column() << ") type '"
	  << _name << "' was not declared in this scope:"
	  << std::endl
	  << _syntax.get_file_line()
	  << std::endl << std::string(_syntax.get_column(), ' ') << "^";
	return ss.str();
      }

      undefined_type::	undefined_type(const AST::node::syntax& _syntax, const std::string& _name)
	: syntax::error(write_msg(_syntax, _name)) {}

      /*
       * non descopable type
       */
      const std::string	non_descopable_type::write_msg(const AST::node::syntax& _syntax, const std::string& _name) {
	std::stringstream ss;

	ss
	  << "at (" << _syntax.get_line() << ", " << _syntax.get_column() << ")"
	  << " attempt to use type '"
	  << _name << "' as a scope:"
	  << std::endl
	  << _syntax.get_file_line()
	  << std::endl << std::string(_syntax.get_column(), ' ') << "^";
	return ss.str();
      }

      non_descopable_type::	non_descopable_type(const AST::node::syntax& _syntax, const std::string& _name)
	: syntax::error(write_msg(_syntax, _name)) {}
      
    };
  };
};
