#ifndef Function_Line_h__
# define Function_Line_h__
# ifndef  INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class FunctionPrototype
  : public GrammarLine
< line_name::function_prototype,
  Or<
    And<
      Match<AST::keyword::Fun>,
      Call<line_name::type_definition>,
      Call<line_name::scoped_id>,
      Call<line_name::argument_list>
      >,
    Match<AST::final::FunctionPrototype>
    >
  > {
public:
  static std::list<AST::node*> onError(std::list<AST::node*> t_list) {
    std::cout
      << "function prototype, error"
      << std::endl;
    return (t_list);
  }
  static std::list<AST::node*> onMatch(std::list<AST::node*> t_list) {
    std::cout
      << "function prototype, match"
      << std::endl;
    return (t_list);
  }
};

#endif
