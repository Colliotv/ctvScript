#include <iostream>
#include "architecture/ASTgrammar.hpp"

# include "data/derived_types.h"

namespace ctvscript {
  namespace AST {
    namespace tree {

      /*
       * Line:: Type Definition
       */
      std::list<AST::node*> TypeDefinition::onError(std::list<AST::node*> t_list) {
	return (t_list);
      }

      std::list<AST::node*> TypeDefinition::onMatch(std::list<AST::node*> t_ASTnodes) {
	std::list<node*>::iterator t_cursor = t_ASTnodes.begin();
	std::list<node*>::iterator t_further = t_ASTnodes.begin();

	bool _const = false;
	if (for_< Match<AST::values::Const> >::organize(t_ASTnodes, t_cursor, t_further))
	  _const = true;
	if (for_< Match<AST::symbol::Bparenthesis> >::organize(t_ASTnodes, t_cursor, t_further)) {
	  std::cout
	    << "imbricated"
	    << std::endl;
	}
  
	std::cout
	  << "type definition, match"
	  << std::endl;
	return (t_ASTnodes);
      }

    };
  };
};
