#ifndef Exception_h__
# define Exception_h__

# include <string>
# include <stdexcept>
# include <cstdlib>

namespace ctvscript {
  namespace utils {
    std::string seize_line(const std::string::const_iterator&, const std::string&);

    class cursor_indicator{
      std::size_t m_line;
      std::size_t m_column;

    public:
      cursor_indicator(std::size_t line, std::size_t column);
      cursor_indicator(const cursor_indicator&);

    public:
      std::size_t getLine() const;
      std::size_t getColumn() const;
    };
  };

  namespace exception {
    class identification_error : public std::logic_error {
    private:
      const utils::cursor_indicator m_cursor;

    private:
      static const std::string write_msg(const utils::cursor_indicator&, const std::string&);

    public:
      identification_error(const utils::cursor_indicator&, const std::string&) noexcept;
      virtual ~identification_error() noexcept;

    public:
      const utils::cursor_indicator& getCursor() const;
    };
  };
};

#endif
