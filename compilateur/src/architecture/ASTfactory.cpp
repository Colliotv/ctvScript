#include "architecture/ASTnode.h"

# define SYNTAX_ALLOCATOR_MEMBER(__typeid, __ast_type) \
  {parser::syntax::identifier::__typeid, {[](){return new __ast_type();}}}

namespace ctvscript {
  namespace AST {
    const std::map< parser::syntax::identifier, std::function<AST::node*()> >factory::m_syntax_ASTallocator({
	SYNTAX_ALLOCATOR_MEMBER(variable, AST::node),
      });
  };
};
