#ifndef ASTBool_operators_h__
# define ASTBool_operators_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Inferior : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::inferior;

public:
  Inferior(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Inferior_equal : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::inferior_equal;

public:
  Inferior_equal(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Superior : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::superior;

public:
  Superior(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Superior_equal : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::superior_equal;

public:
  Superior_equal(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Equality : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::equality;

public:
  Equality(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};


#endif
