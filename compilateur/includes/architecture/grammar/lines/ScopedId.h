#ifndef IdLine_h__
# define IdLine_h__
# ifndef  INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class ScopedIdLine
  : public GrammarLine
< line_name::ScopedId,
  Or<
    And<
      Repeat<
	And<
	  Match<AST::values::Unspecified_typeid>,
	  Match<AST::operands::ScopeResolution>
	  >
	,0 >,
      Match<AST::values::Unspecified_typeid>
      >,
    Match<AST::final::ScopedId>
    >
  > {
public:
  static std::list<AST::node*> onError(std::list<AST::node*> t_list);
  static std::list<AST::node*> onMatch(std::list<AST::node*> t_list);
};

#endif
