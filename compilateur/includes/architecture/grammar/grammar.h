#ifndef FINALGrammar_h__
# define FINALGrammar_h__
# ifndef  INCLUDED_FROM_ASTGRAMMAR
#  error "This file should be included only in ASTgrammar.h"
# endif
# define INCLUDED_FROM_GRAMMAR_LINE

class FunctionDefinitionLine
  : public GrammarLine
< line_name::global, //change to function_definition after testing
  And<
    And<
      Compare<AST::keyword::Fun>,
      Compare<AST::values::Unspecified_typeid>, //need a type line
      Compare<AST::values::Unspecified_typeid>,
      Compare<AST::symbol::Bparenthesis>
      >,
    Repeat<
      And<
	Compare<AST::values::Unspecified_typeid>,
	Compare<AST::values::Unspecified_typeid>,
	Compare<AST::symbol::Comma>
	>
      , 0
      >,
    Repeat<
      And<
	Compare<AST::values::Unspecified_typeid>,
	Compare<AST::values::Unspecified_typeid>
	>
      , 0, 1
      >,
    Compare<AST::symbol::Eparenthesis>
    >
  > {};


typedef GrammarTree< FunctionDefinitionLine > Grammar; 

# undef INCLUDED_FROM_GRAMMAR_LINE
#endif
