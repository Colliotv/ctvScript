#ifndef ASTType_h__
# define ASTType_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Type : public AST::node{

public:
  Type(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
