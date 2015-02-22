#ifndef ASTBinary_h__
# define ASTBinary_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Binary_and : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::binary_and;

public:
  Binary_and(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Binary_or : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::binary_or;

public:
  Binary_or(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Binary_left_shift : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::binary_left_shift;

public:
  Binary_left_shift(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Binary_right_shift : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::binary_right_shift;

public:
  Binary_right_shift(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
