#ifndef ASTVar_h__
# define ASTVar_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Var : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::variable;
};

#endif
