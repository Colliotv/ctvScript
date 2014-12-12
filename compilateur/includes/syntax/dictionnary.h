#ifndef Syntax_h__
# define Syntax_h__

# include <regex>
# include <map>

# define VARIABLE_REGEX(__string__)	std::regex(__string__), 1
# define  SOLID_REGEX(__string__)	std::regex(__string__), sizeof(__string__) - 1

namespace ctvscript {
  namespace parser{

    class syntax {
    public:
      enum class identifier : unsigned char{
	unknown
	  , whitespace
	  , new_line

	  , variable
	  , function
	  , if_statement
	  , else_statement
	  , return_statement

	  , typedef_statement

	  , import_statement

	  , namespace_statement
	  , class_statement
	  , public_statement
	  , private_statement

	  , semicolon
	  , Bparenthesis, Eparenthesis
	  , Bbrackets, Ebrackets
	  , Bsqbrackets, Esqbrackets

	  , scope_resolution
	  , increment
	  , decrement
	  , struct_dereference
	  , struct_reference

	  , colon
	  , addition
	  , substraction
	  , division
	  , modulo
	  , multiplication

	  , type_id
	  };
      struct dictionnary_member { std::regex m_match; size_t m_min_match_size; };
      static const std::map<syntax::identifier, syntax::dictionnary_member> dictionnary;

      typedef std::string::const_iterator		 cursor;
      typedef const std::string::const_iterator		 file_end;
      typedef std::pair<const syntax::identifier, const std::string> typed_response;

    private:
      /* check following syntax */
      static bool check_in_syntax(cursor&, file_end, const dictionnary_member&);

    public:
      /* allow checking of next word type*/
      template<syntax::identifier _id>
      static bool next_word_is(cursor& t_c, file_end t_e) {
	return (check_in_syntax(t_c, t_e, syntax::dictionnary.at(_id)));
      }

      /* retrieve next word type */
      static const typed_response get_next_word_type(cursor&, file_end);
    };

  };
};
#endif
