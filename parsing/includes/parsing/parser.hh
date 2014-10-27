#ifndef Parser_h__
# define Parser_h__

//C includes
# include <string.h>

//Cpp includes
# include <string>
# include <vector>
# include <map>


# include "architecture/node.hh"
# include "architecture/instruction.hh"
# include "architecture/type.hh"

# include "parsing/exception.hh"

/* to define

# archi/eval
# archi/instructs

*/

namespace ctvscript{
  namespace parser {

    namespace detail {
      enum alphabet {
	symbol_alphabet = 0
        ,   keyword_alphabet
	,   int_alphabet
	,   float_alphabet
	,   x_alphabet
	,   hex_alphabet
	,   b_alphabet
	,   bin_alphabet
	,   id_alphabet
	,   white_alphabet
	,   int_suffix_alphabet
	,   float_suffix_alphabet
	,   nline_alphabet
	,   max_alphabet
	,   lengthof_alphabet = 256
      };
    };

    class language_parser{
    private:

      std::string::const_iterator m_input_pos, m_input_end;
      size_t m_line, m_col;

      /* should be moved to a dico class */
      std::string m_multiline_comment_begin, m_multiline_comment_end;
      std::string m_singleline_comment;

      std::vector<architecture::node> m_current_context;


      bool m_alphabet [detail::max_alphabet][detail::lengthof_alphabet];
      typedef bool alphabet[];

      std::map<std::string, architecture::instructions::operations_types> m_operators;

    public:

      language_parser()
	: m_line(0), m_col(0),
	  m_multiline_comment_begin("/*"),
          m_multiline_comment_end("*/"),
          m_singleline_comment("//") { language_default_setup(); }

      void language_default_setup() {
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("?", architecture::instructions::operations_types::ternary));


	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("||", architecture::instructions::operations_types::logical_or));


	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("&&", architecture::instructions::operations_types::logical_and));


	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("^", architecture::instructions::operations_types::bitwise_xor));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("|", architecture::instructions::operations_types::bitwise_or));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("&", architecture::instructions::operations_types::bitwise_and));


	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("==", architecture::instructions::operations_types::equality));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("!=", architecture::instructions::operations_types::equality));


	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >(">=", architecture::instructions::operations_types::comparison));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >(">", architecture::instructions::operations_types::comparison));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("<=", architecture::instructions::operations_types::ternary));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("<", architecture::instructions::operations_types::ternary));

	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("<<", architecture::instructions::operations_types::shift));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >(">>", architecture::instructions::operations_types::shift));

	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("+", architecture::instructions::operations_types::addition));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("-", architecture::instructions::operations_types::addition));


	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("*", architecture::instructions::operations_types::multiplication));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("/", architecture::instructions::operations_types::multiplication));
	m_operators.emplace(std::make_pair<
			    std::string,
			    architecture::instructions::operations_types
			    >("%", architecture::instructions::operations_types::multiplication));

	for ( int c = 0 ; c < detail::lengthof_alphabet ; ++c ) {
          for (auto & elem : m_alphabet) {
            elem[c]=false;
          }
        }
        m_alphabet[detail::symbol_alphabet][static_cast<int>('?')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('+')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('-')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('*')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('/')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('|')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('&')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('^')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('=')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('.')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('<')]=true;
        m_alphabet[detail::symbol_alphabet][static_cast<int>('>')]=true;

        for ( int c = 'a' ; c <= 'z' ; ++c ) { m_alphabet[detail::keyword_alphabet][c]=true; }
        for ( int c = 'A' ; c <= 'Z' ; ++c ) { m_alphabet[detail::keyword_alphabet][c]=true; }
        for ( int c = '0' ; c <= '9' ; ++c ) { m_alphabet[detail::keyword_alphabet][c]=true; }
        m_alphabet[detail::keyword_alphabet][static_cast<int>('_')]=true;

        for ( int c = '0' ; c <= '9' ; ++c ) { m_alphabet[detail::int_alphabet][c]=true; }
        for ( int c = '0' ; c <= '9' ; ++c ) { m_alphabet[detail::float_alphabet][c]=true; }
        m_alphabet[detail::float_alphabet][static_cast<int>('.')]=true;

        for ( int c = '0' ; c <= '9' ; ++c ) { m_alphabet[detail::hex_alphabet][c]=true; }
        for ( int c = 'a' ; c <= 'f' ; ++c ) { m_alphabet[detail::hex_alphabet][c]=true; }
        for ( int c = 'A' ; c <= 'F' ; ++c ) { m_alphabet[detail::hex_alphabet][c]=true; }

        m_alphabet[detail::x_alphabet][static_cast<int>('x')]=true;
        m_alphabet[detail::x_alphabet][static_cast<int>('X')]=true;

        for ( int c = '0' ; c <= '1' ; ++c ) { m_alphabet[detail::bin_alphabet][c]=true; }
        m_alphabet[detail::b_alphabet][static_cast<int>('b')]=true;
        m_alphabet[detail::b_alphabet][static_cast<int>('B')]=true;

        for ( int c = 'a' ; c <= 'z' ; ++c ) { m_alphabet[detail::id_alphabet][c]=true; }
        for ( int c = 'A' ; c <= 'Z' ; ++c ) { m_alphabet[detail::id_alphabet][c]=true; }
        m_alphabet[detail::id_alphabet][static_cast<int>('_')] = true;

        m_alphabet[detail::white_alphabet][static_cast<int>(' ')]=true;
        m_alphabet[detail::white_alphabet][static_cast<int>('\t')]=true;
        m_alphabet[detail::nline_alphabet][static_cast<int>('\n')]=true;

        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('l')] = true;
        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('L')] = true;
        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('u')] = true;
        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('U')] = true;

        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('l')] = true;
        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('L')] = true;
        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('f')] = true;
        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('F')] = true;
      }

      bool check_in_alphabet(unsigned char t_c, detail::alphabet t_d) {
	return m_alphabet[t_d][t_c];
      };



      bool has_more_input() {
	return (m_input_pos != m_input_end);
      }



      bool SkipComment() {
	size_t col = m_col;
	size_t line = m_line;

	if (Symbol_(m_multiline_comment_begin.c_str())) {
	  bool ended = false;
	  while (has_more_input()) {
	    if (Symbol_(m_multiline_comment_end.c_str())) {
	      ended = true;
	      break;
	    } else if (!Eol_()) {
	      ++m_col;
	      ++m_input_pos;
	    }
	  }
	  if (!ended)
	    throw exception::parse_error("Unended Multiline Comment",
					 cursor_position(line, col));
	}
      }

      void SkipWhiteSpace(bool skip_new_line = true) {
	do {
	  if (check_in_alphabet(*m_input_pos, detail::white_alphabet)) {
	    ++m_col;
	    ++m_input_pos;
	  } else if (skip_new_line && check_in_alphabet(*m_input_pos, detail::nline_alphabet)) {
	    m_col = 0;
	    ++m_line;
	    ++m_input_pos;
	  } else if (!SkipComment())
	    return ;
	} while (has_more_input());
      };



      bool KeyWord_(const char* t_keyword) {
	size_t len = strlen(t_keyword);
	if ((m_input_end - m_input_pos) >=
	    static_cast<std::make_signed<size_t>::type>(len)) {
	  std::string::const_iterator tmp = m_input_pos;
	  for (size_t i = 0; i < len; ++i) {
	    if (*tmp != t_keyword[i]) {
	      return false;
	    }
	    ++tmp;
	  }
	  m_input_pos = tmp;
	  m_col += static_cast<std::make_signed<size_t>::type>(len);
	} else
	  return (false);
	return (true);
      };

      bool KeyWord(const char* t_keyword) {
	SkipWhiteSpace();

	size_t col = m_col;
	size_t line = m_line;
	std::string::const_iterator tmp = m_input_pos;
	if (!KeyWord_(t_keyword))
	  return (false);
	m_col = col;
	m_line = line;
	m_input_pos = tmp;
	return (true);
      }




      bool Symbol_(const char* t_keyword) {
	size_t len = strlen(t_keyword);
	if ((m_input_end - m_input_pos) >=
	    static_cast<std::make_signed<size_t>::type>(len)) {
	  std::string::const_iterator tmp = m_input_pos;
	  for (size_t i = 0; i < len; ++i) {
	    if (*tmp != t_keyword[i]) {
	      return false;
	    }
	    ++tmp;
	  }
	  m_input_pos = tmp;
	  m_col += static_cast<std::make_signed<size_t>::type>(len);
	} else
	  return (false);
	return (true);
      };

      bool Symbol(const char* t_keyword) {
	SkipWhiteSpace();

	size_t col = m_col;
	size_t line = m_line;
	std::string::const_iterator tmp = m_input_pos;
	if (!Symbol_(t_keyword))
	  return (false);
	m_col = col;
	m_line = line;
	m_input_pos = tmp;
	return (true);
      }

      bool Char_(char t_char) {
	if (has_more_input() && (*m_input_pos == t_char)) {
	  ++m_input_pos;
	  ++m_col;
	  return (true);
	}
	return (false);
      }

      bool Char(char t_char) {
	SkipWhiteSpace();
	return (Char_(t_char));
      }




      bool BlockEnd_() {
	SkipWhiteSpace();
	return (*m_input_pos == '}');
      };

      bool Eol_() {
	bool retval = false;
	if (*m_input_pos == '\n') {
	  retval = true;
	  ++m_line;
	  m_col = 0;
	  ++m_input_pos;
	}
	return (retval);
      }

      bool Eol() {
	SkipWhiteSpace(false);
	return (Eol_());
      };

      /* Types
       *
       */
      const architecture::type::info*
      Type() {
	SkipWhiteSpace();
	
      }
      /* Decl
       * Variable Declaration
       */


      /* Def
       * Function Or Method
       */
      bool Def() {
	if (!KeyWord("def"))
	  return false;
	const architecture::type::info* _type = Type();

      }


      /*
       * Current Context;
       */
      void Context_() {
	bool has_more = false;
	do {
	  if (BlockEnd_()) {
	    has_more = false;
	  } else if (Eol()) {
	    has_more = true;
	  } else if (Def()) {
	  } else {
	    has_more = false;
	  }
	} while (has_more);
      };

      bool parse(const std::string &t_input) {
	m_input_pos = t_input.begin();
	m_input_end = t_input.end();

	m_line = 0;
	m_col = 0;
	
	Context_();
	if (m_input_pos != m_input_end)
	  throw exception::parse_error("Unparsed Input", cursor_position(m_line, m_col));
	
	return (true);
      }
    };

  };
};
#endif
