#ifndef ASTnode_h__
# define ASTnode_h__
# define INCLUDED_FROM_ASTNODE

# include <map>

#include "syntax/dictionnary.h"
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
      static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::unknown;
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
      class Else;		//: AST::node{}; 

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
      class Bsqbrackets; //: AST::node{};
      class Esqbrackets; //: AST::node{};
    };

# define SYNTAX_BUILDABLE_NODE_LIST	\
    Var,				\
      Fun,				\
      If, Else,				\
      Return,				\
      Typedef,				\
      Import,				\
      SemiColon,			\
      Bparenthesis, Eparenthesis,	\
      Bbracket, Ebracket		\
      

    /*
     * The Factory help in two way: 
		-> Parsing
		-> [...]
     */
    class factory {
    private:
      template<class ... nodes>
      static std::map< parser::syntax::identifier, std::function<AST::node*()> > make_ASTallocator();

      static const std::map<parser::syntax::identifier, std::function<AST::node*()>> m_syntax_ASTallocator;
    };
  };
};

#undef INCLUDED_FROM_ASTNODE
#endif
