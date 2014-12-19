#ifndef TypeLine_h__
# define TypeLine_h__
# ifndef  INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class TypeDefinitionLine
  : public GrammarLine
< line_name::type_definition,
  Or<
    And<
      Repeat<
	Or<
	  Match<AST::values::Const>,
	  Match<AST::symbol::Star>
	  >
	,0 >,
      Match<AST::symbol::Bparenthesis>,
      Call<line_name::type_definition>,
      Match<AST::symbol::Eparenthesis>,
      Repeat<
	Or<
	  And<
	    Match<AST::symbol::Bsqbracket>,
	    Match<AST::values::Integer>,
	    Match<AST::symbol::Esqbracket>
	    >,
	  And<
	    Match<AST::symbol::Bparenthesis>,
	    Repeat<
	      And<
		Call<line_name::type_definition>,
		Match<AST::symbol::Comma>
		>
	      ,0>,
	    Repeat<
	      Call<line_name::type_definition>
	      ,0,1>,
	    Match<AST::symbol::Eparenthesis>
	    >
	  >
	, 0>
      >,
    And<
      Repeat<
	Or<
	  Match<AST::values::Const>,
	  Match<AST::symbol::Star>
	  >
	,0 >,
      Repeat<
	Match<AST::symbol::Reference>
	,0,1>,
      Call<line_name::ScopedId>,
      Repeat<
	Or<
	  And<
	    Match<AST::symbol::Bsqbracket>,
	    Match<AST::values::Integer>,
	    Match<AST::symbol::Esqbracket>
	    >,
	  And<
	    Match<AST::symbol::Bparenthesis>,
	    Repeat<
	      And<
		Call<line_name::type_definition>,
		Match<AST::symbol::Comma>
		>
	      ,0>,
	    Repeat<
	      Call<line_name::type_definition>
	      ,0,1>,
	    Match<AST::symbol::Eparenthesis>
	    >
	  >
	, 0>
      >,
    Match<AST::final::Type>
    >
  > {};

#endif
