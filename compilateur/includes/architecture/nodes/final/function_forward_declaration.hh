#ifndef ASTFunction_Forward_Decl_h__
# define ASTFunction_Forward_Decl_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class FunctionForwardDeclaration : public AST::node{

public:
  FunctionForwardDeclaration(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
