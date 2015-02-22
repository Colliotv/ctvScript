#ifndef ASTArgumentList_h__
# define ASTArgumentList_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class ArgumentsList : public AST::node{
public:
  ArgumentsList(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
