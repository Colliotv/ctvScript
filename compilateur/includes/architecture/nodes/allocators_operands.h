#ifndef ASTAllocator_h__
# define ASTAllocator_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class New : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::new_statement;

public:
  New(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Delete : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::delete_statement;

public:
  Delete(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
