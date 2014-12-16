#ifndef ASTReturn_h__
# define ASTReturn_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Return : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::return_statement;
};

#endif
