#ifndef ASTTypedef_h__
# define ASTTypedef_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Typedef : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::typedef_statement;

public:
  Typedef(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
