#ifndef TypeLine_h__
# define TypeLine_h__
# ifndef  INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class TypeDefinition
  : public GrammarLine
< line_name::type_definition,
  Or<
    And<
      Repeat<
	Match<AST::values::Const>
	, 0, 1>,
      Or<
        And<
          Match<AST::symbol::Bparenthesis>,
          Call<line_name::type_definition>,
          Match<AST::symbol::Eparenthesis>
         >,
	Or<
	  Call<line_name::scoped_type>
	  >
	>,
      Repeat<
	Match<AST::symbol::Star>
	, 0>,
      Repeat<
        Match<AST::symbol::Reference>
	, 0, 1>,
      Repeat<
	And<
	   Match<AST::symbol::Bparenthesis>,
	   Or<
	     And<
	       Repeat<
		 And<
		   Call<line_name::type_definition>,
		   Match<AST::symbol::Comma>
		 >
		 ,0>,
	       Call<line_name::type_definition>
	       >,
	     Repeat<
                Call<line_name::type_definition>
             ,0,1>
           >,
	  Match<AST::symbol::Eparenthesis>
	  >
	, 0, 1>,
      Repeat<
	  And<
	    Match<AST::symbol::Bsqbracket>,
	    Match<AST::values::Integer>,
	    Match<AST::symbol::Esqbracket>
	    >
      , 0>
      >,
  Match<AST::final::Type>
    >
  > {
public:
  static std::list<AST::node*> onError(std::list<AST::node*> t_list);
  static std::list<AST::node*> onMatch(std::list<AST::node*> t_list);
};

#endif
