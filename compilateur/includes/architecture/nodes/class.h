#ifndef ASTClass_h__
# define ASTClass_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Namespace : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::namespace_statement;
};
class Class : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::class_statement;
};
class Public : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::public_statement;
};
class Private : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::private_statement;
};

#endif
