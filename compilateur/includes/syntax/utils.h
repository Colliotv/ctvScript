#ifndef Utils_h__
# define Utils_h__

#include <string>

namespace ctvscript {
  namespace parser {
    struct cursor_data{
      std::string::const_iterator m_cursor;
      size_t m_line; size_t m_column;

      cursor_data(const std::string::const_iterator& t_cursor, size_t t_line, size_t t_column);
      cursor_data(const cursor_data& t_cursor);

      size_t distance(const std::string::const_iterator& t_ahead_cursor);
      size_t distance(const cursor_data& t_ahead_cursor);

      void   assert(const std::string::const_iterator& t_cursor, size_t t_line, size_t t_column);

      void   operator = (const cursor_data& t_cursor);

      bool operator == (const std::string::const_iterator& t_oth);
      bool operator != (const std::string::const_iterator& t_oth);
      operator std::string::const_iterator&();
    };
  };
};

#endif
