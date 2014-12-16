#ifndef FINALGrammar_h__
# define FINALGrammar_h__
# ifndef  INCLUDED_FROM_ASTGRAMMAR
#  error "This file should be included only in ASTgrammar.h"
# endif



typedef GrammarTree<GrammarLine<line_name::global, And<Call<line_name::global> > > > Grammar; 


#endif
