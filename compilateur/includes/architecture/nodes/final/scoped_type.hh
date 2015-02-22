#ifndef ASTScoped_type_h__
# define ASTScoped_type_h__
# ifndef INCLUDED_FROM_ASTNODE
#  error "this file should be inclued only in architecture/ASTnode.h"
# endif

class ScopedType : public AST::node{
private:
  byte_code::data::type::container::interface*	m_type;

public:
  ScopedType(const std::string& t_file_line,
	     const node::syntax& t_node_syntax,
	     byte_code::data::type::container::interface* t_type);

public:
  byte_code::data::type::container::interface*	getType();  
};

#endif
