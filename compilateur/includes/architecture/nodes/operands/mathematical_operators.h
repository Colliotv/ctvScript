#ifndef ASTMathematical_operators_h__
# define ASTMathematical_operators_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Addition : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::addition;

public:
  Addition(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Substraction : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::substraction;

public:
  Substraction(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Division : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::division;

public:
  Division(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Modulo : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::modulo;

public:
  Modulo(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};

class Decrement : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::decrement;

public:
  Decrement(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};
class Increment : public AST::node{
public:
  static const parser::syntax::identifier syntax_identifier = parser::syntax::identifier::increment;

public:
  Increment(const std::string& t_file_line, const node::syntax& t_node_syntax)
    : AST::node(t_file_line, t_node_syntax){}
};


#endif
