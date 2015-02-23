#ifndef ASTType_h__
# define ASTType_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class Type : public AST::node{
private:
  byte_code::data::type::container::interface*	m_type;

public:
  Type(const std::string& t_file_line,
       const node::syntax& t_node_syntax,
       byte_code::data::type::container::interface* t_type);

public:
  byte_code::data::type::container::interface*	getType();  
};

#endif
