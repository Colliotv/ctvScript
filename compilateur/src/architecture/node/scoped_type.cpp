#include "architecture/ASTnode.hh"

namespace ctvscript {
  namespace AST {
    namespace final {

      ScopedType::	ScopedType(const std::string& t_file_line,
				   const node::syntax& t_node_syntax,
				   byte_code::data::type::container::interface* t_type)
	: AST::node(t_file_line, t_node_syntax), m_type(t_type) {}

      byte_code::data::type::container::interface*	ScopedType::getType() {
	return (m_type);
      }
      
    };
  };
};
