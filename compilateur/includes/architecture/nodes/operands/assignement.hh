#ifndef ASTAssignement_h__
# define ASTAssignement_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Assignement : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::assignement;

public:
  Assignement(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
