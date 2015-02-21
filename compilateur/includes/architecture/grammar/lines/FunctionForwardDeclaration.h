#ifndef Function_Forward_Declaration_h__
# define Function_Forward_Declaration_h__
# ifndef INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class FunctionForwardDeclaration
  : public GrammarLine
< line_name::function_forward_declaration,
  Or<
    And<
      Call<line_name::function_prototype>,
      Match<AST::symbol::Semicolon>
      >,
    Match<AST::final::FunctionForwardDeclaration>
    >
  >
{};

#endif
