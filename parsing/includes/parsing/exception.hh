#ifndef Exception_h__
# define Exception_h__

# include <sstream>

namespace ctvscript {
  namespace parser{
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
    format_interval(const cursor_position &t_from, const cursor_position &t_to) {
      std::stringstream ss;
      ss << "from (" << t_from.line << ", " << t_from.column << ") to (" << t_to.line << ", " << t_to.column << ")";
      return ss.str();
    }

    static std::string
    format_type(const std::string& t_type) {
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
	   const cursor_position &t_from,
	   const cursor_position &t_to) {
      std::stringstream ss;

      ss << format_why(t_why) << " " << format_interval(t_from, t_to);;
      return (ss.str());
    }

    static std::string
    format(const std::string &t_why,
	   const cursor_position &t_where,
	   const std::string &t_type) {
      std::stringstream ss;

      ss << format_why(t_why) << " " << format_type(t_type) << " " << format_location(t_where);
      return (ss.str());
    }

    static std::string
    format(const architecture::operations::invalid_operand&,
	   const cursor_position &t_where) {
      std::stringstream ss;
      ss << format_why("operand + can't be predecessed by +") << " " << format_location(t_where) << std::endl;
      return (ss.str());
    }

  };
  namespace exception {
    struct parse_error : public std::runtime_error {
      std::string m_cause;

      const parser::cursor_position m_where;

      parse_error(std::string t_cause, const parser::cursor_position& t_where)
	: std::runtime_error(parser::format(t_cause, t_where)), m_cause(parser::format(t_cause, t_where)), m_where(t_where)
      {}

      parse_error(std::string t_cause, const parser::cursor_position& t_from, const parser::cursor_position& t_to)
	: std::runtime_error(parser::format(t_cause, t_from, t_to)), m_cause(parser::format(t_cause, t_from, t_to)), m_where(t_from)
      {}

      parse_error(std::string t_cause, const parser::cursor_position& t_where, std::string t_type)
	: std::runtime_error(parser::format(t_cause, t_where, t_type)), m_cause(parser::format(t_cause, t_where, t_type)), m_where(t_where)
      {}

      parse_error(const architecture::operations::invalid_operand& e, const parser::cursor_position& t_where)
	: std::runtime_error(parser::format(e, t_where)), m_cause(parser::format(e, t_where)), m_where(t_where) {}
    };
  };
};

#endif
