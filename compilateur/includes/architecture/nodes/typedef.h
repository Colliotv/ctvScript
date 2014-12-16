#ifndef ASTTypedef_h__
# define ASTTypedef_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Typedef : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::typedef_statement;
};

#endif
