#ifndef ASTSemicolon_h__
# define ASTSemicolon_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Semicolon : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::semicolon;
};

#endif
