#ifndef ASTIf_h__
# define ASTIf_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class If : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::if_statement;
};

class Else : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::else_statement;
};

#endif
