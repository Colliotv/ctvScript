#include "architecture/ASTnode.h"

namespace ctvscript {
  namespace AST {
    const std::map< parser::syntax::identifier, std::function<AST::node*()> >
    factory::m_syntax_ASTallocator(make_ASTallocator<SYNTAX_BUILDABLE_NODE_LIST>());

    template<typename __node>
    static AST::node* make_node() { return new __node(); }

    template<typename ... __nodes>
    std::map< parser::syntax::identifier, std::function<AST::node*()> > factory::make_ASTallocator() {
      std::array< parser::syntax::identifier,	sizeof...(__nodes)> keys({
	  __nodes::syntax_identifier...
	    });
      std::array<std::function<AST::node*()>,	sizeof...(__nodes)> values({
	  make_node<__nodes> ...
	    });
      std::map< parser::syntax::identifier, std::function<AST::node*()> > retval;
      for (size_t i = 0; i < sizeof ... (__nodes); ++i) {
	retval.emplace(keys[i], values[i]);
      }
      return retval;
    }
  };
};
