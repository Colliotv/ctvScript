#ifndef ASTnode_h__
# define ASTnode_h__
# define INCLUDED_FROM_ASTNODE

# include <map>

# include "syntax/dictionnary.h"
/*
 * Here is defined the majority of AST nodes
 * implemntation are done in src
 */
namespace ctvscript {
  namespace AST {
    /*
     * This interface will premit easier tree/list constructing
     */
    class node {
    public:
      class syntax {
      private:
	const std::string	m_file_line;
	const std::size_t	m_column;
	const std::size_t	m_line;

      public:
	syntax(const std::string&, std::size_t, std::size_t);
      };
      static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::unknown;

    public:
      node(const std::string&, const node::syntax&);

    private:
      const std::string&	m_file_line;
      const node::syntax&	m_syntax;
    };

    /*
     * A key word is language specs
     */
    namespace keyword {
      #include "nodes/var.h"
      class Var;	//: AST::node{};

      #include "nodes/fun.h"
      class Fun;	//: AST::node{};

      #include "nodes/if_else.h"
      class If;		//: AST::node{}; 
      class Else;	//: AST::node{}; 

      #include "nodes/return.h"
      class Return;	//: AST::node{};

      #include "nodes/typedef.h"
      class Typedef;	//: AST::node{};

      #include "nodes/import.h"
      class Import;	//: AST::node{};

      #include "nodes/class.h"
      class Namespace;
      class Class;
      class Public;
      class Private;

    };

    /*
     * Symbols
     */
    namespace symbol {
      #include "nodes/semicolon.h"
      class Semicolon;	 //: AST::node{};

      #include "nodes/colon.h"
      class Colon;	 //: AST::node{};

      #include "nodes/parenthesis.h"
      class Bparenthesis;//: AST::node{};
      class Eparenthesis;//: AST::node{};

      #include "nodes/brackets.h"
      class Bbracket;	 //: AST::node{};
      class Ebracket;	 //: AST::node{};

      #include "nodes/squarebrackets.h"
      class Bsqbracket; //: AST::node{};
      class Esqbracket; //: AST::node{};
    };

    /*
     * Operands
     */
    namespace operands {
      #include "nodes/allocators_operands.h"
      class New;	 //: AST::node{};
      class Delete;	 //: AST::node{};

      #include "nodes/binary_operators.h"
      class Binary_and;	 //: AST::node{};
      class Binary_or;	 //: AST::node{};
      class Binary_left_shift;	 //: AST::node{};
      class Binary_right_shift;	 //: AST::node{};

      #include "nodes/assignement.h"
      class Assignement;

      #include "nodes/mathematical_operators.h"
      class Addition;		//: AST::node{};
      class Substraction;	//: AST::node{};
      class Division;		//: AST::node{};
      class Modulo;		//: AST::node{};
      class Multiplication;	//: AST::node{};

      #include "nodes/comparison.h"
      class Or;
      class And;

      #include "nodes/bool_operators.h"
      class Inferior;
      class Inferior_equal;
      class Superior;
      class Superior_equal;
      class Equality;
    };

    /*
     * Values
     */
    namespace values {
      #include "nodes/unspecified_typeid.h"
      class Unspecified_typeid;	 //: AST::node{};

      #include "nodes/string_litteral.h"
      class String;
      class Char;

      #include "nodes/floating.h"
      class Floating;

      #include "nodes/integer.h"
      class Integer;

    }

# define SYNTAX_BUILDABLE_NODE_LIST					\
    keyword::Var,							\
      keyword::Fun,							\
      keyword::If, keyword::Else,					\
      keyword::Return,							\
      keyword::Typedef,							\
      keyword::Import,							\
      keyword::Namespace,						\
      keyword::Class, keyword::Public, keyword::Private,		\
      symbol::Semicolon,						\
      symbol::Colon,							\
      symbol::Bparenthesis, symbol::Eparenthesis,			\
      symbol::Bbracket, symbol::Ebracket,				\
      symbol::Bsqbracket, symbol::Esqbracket,				\
      operands::New, operands::Delete,					\
      operands::Binary_and, operands::Binary_or,			\
      operands::Binary_left_shift, operands::Binary_right_shift,	\
      operands::Assignement,						\
      operands::Addition, operands::Substraction,			\
      operands::Multiplication,						\
      operands::Division, operands::Modulo,				\
      operands::Or, operands::And,					\
      operands::Inferior, operands::Inferior_equal,			\
      operands::Superior, operands::Superior_equal,			\
      operands::Equality,						\
      values::Unspecified_typeid,					\
      values::String, values::Char,					\
      values::Floating, values::Integer

    /*
     * The Factory help in two way: 
		-> Parsing
		-> [...]
     */
    class factory {
    private:
      static const std::map<parser::syntax::identifier, std::function<AST::node*(const std::string&, const node::syntax&)> >
	m_syntax_ASTallocator;

    public:
      static AST::node* create_node_by_syntax(parser::syntax::identifier, const std::string&, const node::syntax&);
    };
  };
};

#undef INCLUDED_FROM_ASTNODE
#endif
