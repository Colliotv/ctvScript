#ifndef FINALGrammar_h__
# define FINALGrammar_h__
# ifndef  INCLUDED_FROM_ASTGRAMMAR
#  error "This file should be included only in ASTgrammar.h"
# endif
# define INCLUDED_FROM_GRAMMAR_LINE


# include "lines/GlobalState.h"
class GlobalState;

# include "lines/FunctionLine.h"
class FunctionDefinitionLine;

# include "lines/ArgumentListLine.h" // != CallerParameterList
class ArgumentListLine;

# include "lines/TypeLine.h"
class TypeDefinitionLine;

# include "lines/ScopedId.h"
class ScopedIdLine;

typedef GrammarTree< GlobalState, FunctionDefinitionLine, TypeDefinitionLine, ArgumentListLine, ScopedIdLine > Grammar; 

# undef INCLUDED_FROM_GRAMMAR_LINE
#endif
