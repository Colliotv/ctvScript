#ifndef ASTString_Litteral_h__
# define ASTString_Litteral_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class String : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::string_litteral;

public:
  String(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Char : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::char_litteral;

public:
  Char(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

#endif
