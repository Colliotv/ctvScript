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

# define SYNTAX_BUILDABLE_NODE_LIST				\
    keyword::Var,						\
      keyword::Fun,						\
      keyword::If, keyword::Else,				\
      keyword::Return,						\
      keyword::Typedef,						\
      keyword::Import,						\
      keyword::Namespace,					\
      keyword::Class, keyword::Public, keyword::Private,	\
      symbol::Semicolon,					\
      symbol::Bparenthesis, symbol::Eparenthesis,		\
      symbol::Bbracket, symbol::Ebracket,			\
      symbol::Bsqbracket, symbol::Esqbracket
      

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
