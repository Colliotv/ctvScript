#ifndef FINALGrammar_h__
# define FINALGrammar_h__
# ifndef  INCLUDED_FROM_ASTGRAMMAR
#  error "This file should be included only in ASTgrammar.h"
# endif
# define INCLUDED_FROM_GRAMMAR_LINE


# include "lines/GlobalState.hpp"
class GlobalState;

# include "lines/FunctionPrototype.hpp"
class FunctionPrototype;

# include "lines/FunctionForwardDeclaration.hpp"
class FunctionForwardDeclaration;

# include "lines/ArgumentListLine.hpp"
class ArgumentListLine;

# include "lines/TypeDefinition.hpp"
class TypeDefinition;

# include "lines/ScopedId.hpp"
class ScopedId;

# include "lines/ScopedType.hpp"
class ScopedType;

using Grammar = GrammarTree< GlobalState, FunctionForwardDeclaration, FunctionPrototype, TypeDefinition, ArgumentListLine, ScopedId, ScopedType >; 

# undef INCLUDED_FROM_GRAMMAR_LINE
#endif
