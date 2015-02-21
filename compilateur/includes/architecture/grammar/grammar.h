#ifndef FINALGrammar_h__
# define FINALGrammar_h__
# ifndef  INCLUDED_FROM_ASTGRAMMAR
#  error "This file should be included only in ASTgrammar.h"
# endif
# define INCLUDED_FROM_GRAMMAR_LINE


# include "lines/GlobalState.h"
class GlobalState;

# include "lines/FunctionPrototype.h"
class FunctionPrototype;

# include "lines/FunctionForwardDeclaration.h"
class FunctionForwardDeclaration;

# include "lines/ArgumentListLine.h" // != CallerParameterList
class ArgumentListLine;

# include "lines/Type.h"
class TypeDefinition;

# include "lines/ScopedId.h"
class ScopedId;

# include "lines/ScopedType.h"
class ScopedType;

using Grammar = GrammarTree< GlobalState, FunctionForwardDeclaration, FunctionPrototype, TypeDefinition, ArgumentListLine, ScopedId, ScopedType >; 

# undef INCLUDED_FROM_GRAMMAR_LINE
#endif
