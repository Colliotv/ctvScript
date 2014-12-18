#ifndef ArgListLine_h__
# define ArgListLine_h__
# ifndef  INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class ArgumentListLine
  : public GrammarLine
< line_name::argument_list,
  Or<
    And<
      Match<AST::symbol::Bparenthesis>,
      Repeat<
	And<
	  Call<line_name::type_definition>,
	  Call<line_name::ScopedId>,
	  Match<AST::symbol::Comma>
	  >
	,0>,
      Repeat<
	And<
	  Call<line_name::type_definition>,
	  Call<line_name::ScopedId>
	  >
	,0,1>,
      Match<AST::symbol::Eparenthesis>
      >,
    Match<AST::final::ArgumentsList>
    >
  >{}; 

#endif
