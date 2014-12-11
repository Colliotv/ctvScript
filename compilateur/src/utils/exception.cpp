#include <sstream>

#include "utils/exception.h"

namespace ctvscript {
  namespace utils {
    std::string seize_line(const std::string::const_iterator& t_cursor_line, const std::string& t_file) {
      std::string::const_iterator line_beg = t_cursor_line;
      std::string::const_iterator line_end = t_cursor_line;

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
    const std::string identification_error::write_msg(const utils::cursor_indicator& t_cursor, const std::string& t_line) {
      std::stringstream ss;
      ss 
	<<"at ("<< t_cursor.getLine() <<", "<< t_cursor.getColumn() <<") symbols or formula not recognized by dictionnary:"
	<< std::endl << t_line
	<< std::endl << std::string(t_cursor.getColumn(), ' ') << "^";
      return ss.str();
    }

    identification_error::identification_error(const utils::cursor_indicator& t_cursor, const std::string& t_line) noexcept
    : std::logic_error(write_msg(t_cursor, t_line)), m_cursor(t_cursor) {}
    identification_error::~identification_error() noexcept {}

    const utils::cursor_indicator& identification_error::getCursor() const { return m_cursor; }
  };
};
