#ifndef ASTConst_h__
# define ASTConst_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Const : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::const_statement;

public:
  Const(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Static : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::static_statement;

public:
  Static(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
