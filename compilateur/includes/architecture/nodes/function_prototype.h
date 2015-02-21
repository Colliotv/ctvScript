#ifndef ASTFunction_h__
# define ASTFunction_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class FunctionPrototype : public AST::node{

public:
  FunctionPrototype(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
