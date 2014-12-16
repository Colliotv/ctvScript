#ifndef ASTImport_h__
# define ASTImport_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Import : AST::node{
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::import_statement;
};

#endif
