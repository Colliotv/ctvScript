#include "architecture/ASTnode.h"

namespace ctvscript {
  namespace AST {

    /* ##  Node:: syntax  ## */
    node::syntax::	syntax(const std::string& t_file_line, std::size_t t_column, std::size_t t_line)
      : m_file_line(t_file_line), m_column(t_column), m_line(t_line) {}

    std::string		node::syntax::get_file_line() const { return m_file_line; }
    std::size_t		node::syntax::get_column() const { return m_column; }
    std::size_t		node::syntax::get_line() const { return m_line; }


    /* ## Node:: Ctor ## */
    node::node(const std::string& t_string_syntax, const node::syntax& t_syntax)
      : m_string_syntax(t_string_syntax), m_syntax(t_syntax) {}

    /* ## Factory:: syntax_map ## */
    template<typename __node>
    static AST::node* make_node(const std::string& t_file_line, const node::syntax& t_node_syntax) {
      return new __node(t_file_line, t_node_syntax);
    }

    template<typename ... __nodes>
    std::map< parser::syntax::identifier, std::function<AST::node*(const std::string&, const node::syntax&)> >
	make_ASTallocator() {
      std::map< parser::syntax::identifier, std::function<AST::node*(const std::string&, const node::syntax&)> > retval({
	  {parser::syntax::identifier(__nodes::syntax_identifier),  make_node<__nodes>}...
	    });
      return retval;
    }

    const std::map< parser::syntax::identifier, std::function<AST::node*(const std::string&, const node::syntax&)> >
    factory::m_syntax_ASTallocator(make_ASTallocator<SYNTAX_BUILDABLE_NODE_LIST>());

    /* ## Factory:: create_node_by_syntax ## */
    AST::node* AST::factory::create_node_by_syntax(parser::syntax::identifier t_identifier
						   , const std::string& t_file_line, const node::syntax& t_node_syntax) {
      if (m_syntax_ASTallocator.find(t_identifier) == m_syntax_ASTallocator.end())
	return (nullptr);
      return (m_syntax_ASTallocator.at(t_identifier)(t_file_line, t_node_syntax));
    }
  };
};
