#include "syntax/utils.h"

namespace ctvscript {
  namespace parser {

    cursor_data::cursor_data(const std::string::const_iterator& t_cursor, size_t t_line, size_t t_column)
      : m_cursor(t_cursor), m_line(t_line), m_column(t_column) {}

    cursor_data::cursor_data(const cursor_data& t_cursor)
      : m_cursor(t_cursor.m_cursor), m_line(t_cursor.m_line), m_column(t_cursor.m_column) {}

    size_t cursor_data::distance(const std::string::const_iterator& t_ahead_cursor) {
      return (std::distance(m_cursor, t_ahead_cursor));
    }

    size_t cursor_data::distance(const cursor_data& t_ahead_cursor) {
      return (std::distance(m_cursor, (std::string::const_iterator&)t_ahead_cursor));
    }

    void   cursor_data::assert(const std::string::const_iterator& t_cursor, size_t t_line, size_t t_column) {
      m_cursor = t_cursor; m_line = t_line; m_column = t_column;
    }

    void   cursor_data::operator = (const cursor_data& t_cursor) {
      m_cursor = t_cursor.m_cursor; m_line = t_cursor.m_line; m_column = t_cursor.m_column;
    }

    bool cursor_data::operator == (const std::string::const_iterator& t_oth) { return (m_cursor == t_oth); }
    bool cursor_data::operator != (const std::string::const_iterator& t_oth) { return (m_cursor != t_oth); }
    cursor_data::operator std::string::const_iterator&() { return (m_cursor); }


  };
};
