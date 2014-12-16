#ifndef ASTFun_h__
# define ASTFun_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Fun : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::function;
};

#endif
