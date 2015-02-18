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
	  Repeat<
	    Match<AST::values::Unspecified_typeid>
	    ,0,1>,
	  Match<AST::symbol::Comma>
	  >
	,0>,
      Repeat<
	And<
	  Call<line_name::type_definition>,
	  Repeat<
	    Match<AST::values::Unspecified_typeid>
	    ,0,1>
	  >
	,0,1>,
      Match<AST::symbol::Eparenthesis>
      >,
    Match<AST::final::ArgumentsList>
    >
  > {
public:
  static std::list<AST::node*> onError(std::list<AST::node*> t_list) {
    std::cout
      << "argument list line, error"
      << std::endl;
    return (t_list);
  }
  static std::list<AST::node*> onMatch(std::list<AST::node*> t_list) {
    std::cout
      << "argument list line, match"
      << std::endl;
    return (t_list);
  }
};

#endif
