#ifndef ASTClass_h__
# define ASTClass_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Namespace : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::namespace_statement;

public:
  Namespace(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};
class Class : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::class_statement;

public:
  Class(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};
class Public : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::public_statement;

public:
  Public(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};
class Private : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::private_statement;

public:
  Private(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
