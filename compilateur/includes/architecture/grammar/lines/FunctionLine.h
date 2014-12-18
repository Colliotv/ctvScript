#ifndef Function_Line_h__
# define Function_Line_h__
# ifndef  INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class FunctionDefinitionLine
  : public GrammarLine
< line_name::function_definition,
  Or<
    And<
      Match<AST::keyword::Fun>,
      Call<line_name::type_definition>,
      Call<line_name::ScopedId>,
      Call<line_name::argument_list>
      >,
    Match<AST::final::Function>
    >
  > {};

#endif
