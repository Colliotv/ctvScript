#ifndef Exception_h__
# define Exception_h__

# include <sstream>

namespace ctvscript {
  namespace parser{
    struct cursor_position {
      int line;
      int column;

      cursor_position(int t_file_line, int t_file_column)
	: line(t_file_line), column(t_file_column) { }

      cursor_position() : line(0), column(0) { }
    };

    static std::string
    format_why(const std::string &t_why) {
        return "Error: \"" + t_why + "\"";
    }

    static std::string
    format_location(const cursor_position &t_where) {
      std::stringstream ss;
      ss << "at (" << t_where.line << ", " << t_where.column << ")";
      return ss.str();
    }

    static std::string
    format_type(const char* t_type) {
      std::stringstream ss;
      ss << "{ " << t_type << " }";
      return (ss.str());
    }

    /* error format */
    static std::string
    format(const std::string &t_why,
	   const cursor_position &t_where) {
      std::stringstream ss;

      ss << format_why(t_why) << " " << format_location(t_where);;
      return (ss.str());
    }

    static std::string
    format(const std::string &t_why,
	   const cursor_position &t_where,
	   const char* t_type) {
      std::stringstream ss;

      ss << format_why(t_why) << " " << format_type(t_type) << " " << format_location(t_where);
      return (ss.str());
    }

  };
  namespace exception {
    struct parse_error : public std::runtime_error {
      std::string cause;

      parser::cursor_position start_position;
      parser::cursor_position end_position;

      parse_error(std::string t_cause, const parser::cursor_position& t_where)
	: std::runtime_error(parser::format(t_cause, t_where)),
	  cause(t_cause), start_position(t_where)
      {}

      parse_error(std::string t_cause, const parser::cursor_position& t_where, const char* t_type)
	: std::runtime_error(parser::format(t_cause, t_where, t_type)),
	  cause(t_cause), start_position(t_where)
      {}
    };
  };
};

#endif
