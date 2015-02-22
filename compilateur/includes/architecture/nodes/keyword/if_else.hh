#ifndef ASTIf_h__
# define ASTIf_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class If : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::if_statement;

public:
  If(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Else : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::else_statement;

public:
  Else(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
