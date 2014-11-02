#ifndef Parser_h__
# define Parser_h__

//C includes
# include <string.h>

//Cpp includes
# include <iostream>
# include <string>
# include <list>
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
	,   any_alphabet
        ,   keyword_alphabet
	,   int_alphabet
	,   float_alphabet
	,   x_alphabet
	,   hex_alphabet
	,   b_alphabet
	,   bin_alphabet
	,   type_alphabet
	,   id_alphabet
	,   white_alphabet
	,   int_suffix_alphabet
	,   float_suffix_alphabet
	,   nline_alphabet
	,   pointeur_alphabet
	,   max_alphabet
	,   lengthof_alphabet = 256
      };
    };

    class language_parser{
    private:

      struct cursor_save {
	language_parser* m_parser;
	std::string::const_iterator m_it;
	size_t m_line, m_col;
	cursor_save(language_parser* t_parser)
	  : m_parser(t_parser), m_it(t_parser->m_input_pos),
	    m_line(t_parser->m_line), m_col(t_parser->m_col) {}
	void restore() {
	  m_parser->m_input_pos = m_it;
	  m_parser->m_line = m_line;
	  m_parser->m_col = m_col;
	  m_parser->m_line_beg = m_parser->m_input_pos;
	  while (m_parser->m_line_beg != m_parser->m_input_beg &&
		 !m_parser->check_in_alphabet(*(m_parser->m_line_beg),
					      detail::nline_alphabet)) {
	    --m_parser->m_line_beg;
	  }
	  m_parser->matchEndLine();
	}

      };
      std::string::const_iterator m_input_beg, m_input_pos, m_input_end;
      std::string::const_iterator m_line_beg, m_line_end;

      size_t m_line, m_col;

      /* should be moved to a dico class */
      std::string m_multiline_comment_begin, m_multiline_comment_end;
      std::string m_singleline_comment;

      architecture::context_node*	m_superior_context;
      std::list<architecture::node*>	m_current_context;


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
	  m_alphabet[detail::any_alphabet][c] = true;
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

        for ( int c = 'a' ; c <= 'z' ; ++c ) { m_alphabet[detail::type_alphabet][c]=true; }
        for ( int c = 'A' ; c <= 'Z' ; ++c ) { m_alphabet[detail::type_alphabet][c]=true; }
        for ( int c = '0' ; c <= '9' ; ++c ) { m_alphabet[detail::type_alphabet][c]=true; }
        m_alphabet[detail::type_alphabet][static_cast<int>('_')]=true;


        m_alphabet[detail::pointeur_alphabet][static_cast<int>('*')]=true;
        m_alphabet[detail::pointeur_alphabet][static_cast<int>('[')]=true;
        m_alphabet[detail::pointeur_alphabet][static_cast<int>(']')]=true;

        for ( int c = 'a' ; c <= 'z' ; ++c ) { m_alphabet[detail::id_alphabet][c]=true; }
        for ( int c = 'A' ; c <= 'Z' ; ++c ) { m_alphabet[detail::id_alphabet][c]=true; }
        m_alphabet[detail::id_alphabet][static_cast<int>('_')] = true;

        m_alphabet[detail::white_alphabet][static_cast<int>(' ')]=true;
        m_alphabet[detail::white_alphabet][static_cast<int>('\t')]=true;
        m_alphabet[detail::nline_alphabet][static_cast<int>('\n')]=true;

        m_alphabet[detail::any_alphabet][static_cast<int>(' ')]=false;
        m_alphabet[detail::any_alphabet][static_cast<int>('\t')]=false;
        m_alphabet[detail::any_alphabet][static_cast<int>('\n')]=false;

        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('l')] = true;
        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('L')] = true;
        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('u')] = true;
        m_alphabet[detail::int_suffix_alphabet][static_cast<int>('U')] = true;

        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('l')] = true;
        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('L')] = true;
        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('f')] = true;
        m_alphabet[detail::float_suffix_alphabet][static_cast<int>('F')] = true;
      }

      const std::list<architecture::node*>
      cutContext(std::list< architecture::node* >::iterator t_split) {
	std::list<architecture::node*> _tmp(t_split, m_current_context.end());
	m_current_context.erase(t_split, m_current_context.end());
	return (std::move(_tmp));
      }
	
      bool check_in_alphabet(unsigned char t_c, detail::alphabet t_d) {
	return m_alphabet[t_d][t_c];
      };

      bool check_word_in_alphabet(const char* t_word, detail::alphabet t_d) {
	size_t size = strlen(t_word);

	for (size_t i = 0; i < size; i++)
	  if (!check_in_alphabet(t_word[i], t_d))
	    return (false);
	return (true);
      }


      bool has_more_input() {
	return (m_input_pos != m_input_end);
      }

      void matchEndLine() {
	m_line_end = m_line_beg;
	while (m_line_end != m_input_end
	       && !check_in_alphabet(*m_line_end,
				    detail::nline_alphabet))
	  ++m_line_end;
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
	  return (true);
	}
	else if (Symbol_(m_singleline_comment.c_str())) {
	  while (has_more_input() &&
		 !check_in_alphabet(*m_input_pos, detail::nline_alphabet)) {
	    if (check_in_alphabet(*m_input_pos, detail::nline_alphabet)) {
	      m_col = 0;
	      ++m_line;
	      ++m_input_pos;
	      m_line_beg = m_input_pos;
	      matchEndLine();
	    } else {
	      ++m_input_pos;
	      ++m_col;
	    }
	  }
	  return (true);
	}
	return (false);
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
	    m_line_beg = m_input_pos;
	    matchEndLine();
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

	cursor_save _save(this);
	if (KeyWord_(t_keyword))
	  return (true);
	_save.restore();
	return (false);
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

	cursor_save _save(this);
	if (Symbol_(t_keyword))
	  return (true);
	_save.restore();
	return (false);
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

      std::string cutFollowingWord(detail::alphabet t_d) {
	SkipWhiteSpace();
	if (!has_more_input())
	  return (NULL);
	std::string::const_iterator last = m_input_pos;
	while (has_more_input() && check_in_alphabet(*m_input_pos, t_d)) {
	  ++m_input_pos;
	  ++m_col;
	}
	return (std::string(last, m_input_pos));
      }


      bool BlockEnd_() {
	SkipWhiteSpace();
	return (*m_input_pos == '}');
      };

      bool Eol_() {
	bool retval = false;
	if (*m_input_pos == ';') {
	  retval = true;
	  ++m_col;
	  ++m_input_pos;
	}
	return (retval);
      }

      bool Eol() {
	SkipWhiteSpace(false);
	return (Eol_());
      }

      /* Types
       *  Suffixs
       */
      architecture::type::info*
      Type_Suffix_(architecture::type::info* t_type, bool t_pointeur = true) {
	while (has_more_input()) {
	  SkipWhiteSpace();
	  std::list<architecture::node*>::iterator currentContext = m_current_context.end();
	  if (t_pointeur && Char('*')) {
	    t_type = architecture::type::make_pointeur(t_type);
	  } else if (t_pointeur && ParametersList(false)) {
	    architecture::type::callable_info* t_function_type
	      = architecture::type::make_callable(t_type);
	    for (std::list<architecture::node*>::iterator tmp = currentContext;
		 tmp != m_current_context.end(); ++tmp) {
	      if (!dynamic_cast<architecture::type_node*>(*tmp))
		std::cerr << "the FUCK?!" << std::endl;
	      else
		t_function_type
		  ->registerParameters(dynamic_cast<architecture::type_node*>(*tmp)
				       ->getTypeInfo());
	      delete *tmp;
	    }
	    m_current_context.erase(currentContext, m_current_context.end());
	    t_type = t_function_type;
	  } else if (Char('[')) {
	    size_t _array_size = 0;
	    try { _array_size = stoul(cutFollowingWord(detail::int_alphabet)); }
	    catch (...) { throw (exception::parse_error("invalid size declaration in array",
					     cursor_position(m_col, m_line))); }
	    if (!Char(']'))
	      throw (exception::parse_error("invalid size declaration in array",
				 cursor_position(m_col, m_line)));
	    t_type = architecture::type::make_array(t_type, _array_size);
	  } else if (KeyWord("const")) {
	    t_type->registerModifier(architecture::type::modifier::_const);
	  } else {
	    return (t_type);
	  }
	}

	return (t_type);
      }

      architecture::type::info*
      Type_Suffix(architecture::type::info* t_type_info, bool t_pointeur = true) {
	SkipWhiteSpace();
	return (Type_Suffix_(t_type_info, t_pointeur));
      }      

      /* Types
       *
       */
      architecture::type::info*
      Type_() {
	std::string			potent_type = cutFollowingWord(detail::type_alphabet);
	architecture::type::modifier	potent_modifier_type = architecture::type::modifier::none;
	const architecture::type::info* type_info = NULL;
	cursor_save _save(this);

	while ((type_info = architecture::type::getTypeInfo(potent_type.c_str())) == NULL) {
	  if ((potent_modifier_type = architecture::type::getModifier(potent_type.c_str(),
								      potent_modifier_type))
	      == architecture::type::modifier::none){
	    throw exception::parse_error("Unknown Type", cursor_position(m_line, m_col),
					 std::string(potent_type));
	  }
	  potent_type = cutFollowingWord(detail::type_alphabet).c_str();
	}

	while (Symbol("::")) { /* nested type*/
	  cursor_save _nested_save(this);

	  std::string nested_type = cutFollowingWord(detail::type_alphabet);
	  if (architecture::type::is_constructor(type_info, nested_type)) {
	    if (potent_modifier_type != architecture::type::modifier::none)
	      throw exception::parse_error("Type Modifier for Constructor {" + nested_type + "}",
					   cursor_position(m_line, m_col));
	    _save.restore();
	    return (architecture::type::make_type(type_info,
						  architecture::type::modifier::none));
	  }
	  if (architecture::type::is_nested_type(type_info, nested_type))
	    type_info = architecture::type::make_nested_type(type_info, nested_type);
	  else {
	    _nested_save.restore();
	    throw exception::parse_error(nested_type + " is not a nested type of ",
					 cursor_position(m_line, m_col), type_info->m_name);
	  }
	}
	return (architecture::type::make_type(type_info, potent_modifier_type));
      }

      architecture::type::info*
      Type() {
	SkipWhiteSpace();
	return (Type_());
      }

      bool TypedDeclaration() {
	architecture::type::info* _type = Type();
	_type = Type_Suffix(_type);
	std::string variable_name = cutFollowingWord(detail::id_alphabet);
	if (variable_name.empty())
	  throw exception::parse_error("unended variable declaration",
				       cursor_position(m_line, m_col));
	_type = Type_Suffix(_type, false);
	m_current_context.emplace_back(new architecture::variable_node(_type, variable_name));
	return (true);
      }

      /* Var
       * Variable Declaration
       */
      bool Var() {
	if (!KeyWord("var"))
	  return (false);
	return (TypedDeclaration());
      }

      /* ParametersList
       * all's said
       */
      bool ParametersList(bool t_defined = true) {
	if (!Char('('))
	  return (false);
	if (!Char(')')) {
	  do {
	    if (t_defined)
	      TypedDeclaration();
	    else {
	      architecture::type::info* _type = Type();
	      _type = Type_Suffix(_type);
	      _type = Type_Suffix(_type, false);
	      m_current_context.emplace_back(new architecture::type_node(_type));
	    }
	  } while (Char(','));
	if (!Char(')'))
	  throw exception::parse_error("Unended Parameter List Declaration",
				       cursor_position(m_line, m_col));
	}
	return (true);
      }
      
      /* Def
       * Function Or Method
       */
      bool Def() {
	if (!KeyWord("def"))
	  return false;
	SkipWhiteSpace();
	if (!has_more_input())
	  throw exception::parse_error("Unended Function Declaration",
				       cursor_position(m_line, m_col));

	/* fetch Type */
	architecture::type::info* _type = Type();
	_type = Type_Suffix(_type);
	
	/* fetch Function Id */
	std::string function_name = cutFollowingWord(detail::id_alphabet);
	if (function_name.empty())
	  throw exception::parse_error("Unended Function Declaration",
				       cursor_position(m_line, m_col));

	
	/* push Context */
	std::list<architecture::node*>::iterator currentContext = m_current_context.end();

	/* fetch Parameters*/
	if (!ParametersList())
	  throw exception::parse_error("Missing funtion parameters",
				       cursor_position(m_line, m_col));
	architecture::function_node* _function = new architecture::
	  function_node(_type, function_name);
	if (!Char('{'))
	  throw exception::parse_error("No function body for function{" +
				       function_name + "}",
				       cursor_position(m_line, m_col));
	for (std::list<architecture::node*>::iterator tmp = currentContext;
	     tmp != m_current_context.end(); ++tmp)
	  if (!dynamic_cast<architecture::variable_node*>(*tmp))
	    std::cerr << "the FUCK?!" << std::endl;
	  else
	    _function->registerParameters((dynamic_cast<architecture::variable_node*>(*tmp))
					  ->getTypeInfo());

	/* register Context */
	Context();
	if (!Char('}'))
	  throw exception::parse_error("Unterminated function body for function{" + function_name + "}",
				       cursor_position(m_line, m_col));
 	_function->setBody(new architecture::context_node(cutContext(currentContext)));

	/* push symbol into superior context */
	m_current_context.emplace_back(_function);
	return (true);
      }


      /*
       * Current Context;
       */
      void Context() {
	bool has_more = false;
	bool need_eol = false;
	do {
	  if (BlockEnd_()) {
	    need_eol = false;
	    has_more = false;
	  } else if (Eol()) {
	    need_eol = false;
	    has_more = true;
	  } else if (Var()) {
	    has_more = true;
	    need_eol = true;
	  } else if (Def()) {
	    has_more = true;
	    need_eol = false;
	  } else {
	    has_more = false;
	    need_eol = false;
	  }
	  if (need_eol && !Eol()) {
	    throw exception::parse_error("Expected ; before " + cutFollowingWord(detail::any_alphabet)
					 + " token",
					 cursor_position(m_line, m_col));
	  }
	} while (has_more);
      };

      bool parse(const std::string &t_input) {

	m_input_beg = t_input.begin();
	m_input_pos = t_input.begin();
	m_input_end = t_input.end();

	m_line_beg = m_input_pos;
	matchEndLine();

	m_line = 0;
	m_col = 0;

	try {
	  Context();
	  if (m_input_pos != m_input_end)
	    throw exception::parse_error("Unparsed Input", cursor_position(m_line, m_col));
	} catch (exception::parse_error e) {
	  std::cerr << "Syntax Error"  << std::endl;
	  std::cerr << e.m_cause << std::endl;
	  std::cerr << std::endl << std::string(m_line_beg, m_line_end) << std::endl;
	  std::cerr << std::string(e.m_where.column, ' ') << "^" << std::endl;
	  return (false);
	}
	return (true);
      }
    };

  };
};
#endif
