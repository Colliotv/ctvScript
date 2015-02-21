#ifndef ASTComparison_h__
# define ASTComparison_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class And : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::and_symbol;

public:
  And(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Or : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::or_symbol;

public:
  Or(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
