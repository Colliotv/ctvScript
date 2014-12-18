#ifndef GlState_h__
# define GlState_h__
# ifndef  INCLUDED_FROM_GRAMMAR_LINE
#  error "This file should be included only in ASTgrammar.h"
# endif

class GlobalState
  : public GrammarLine
< line_name::global,
  Repeat<
    Or<
      Call<line_name::function_definition>
      >
    ,0>
  >{};

#endif
