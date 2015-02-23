#include <iostream>
#include "architecture/ASTgrammar.hpp"

# include "data/derived_types.hh"

namespace ctvscript {
  namespace AST {
    namespace tree {

      /*
       * Line:: Type Definition
       */
      std::list<AST::node*> TypeDefinition::onError(std::list<AST::node*> t_list) {
	std::cout
	  << "type definition, error"
	  << std::endl;
	return (t_list);
      }

      std::list<AST::node*> TypeDefinition::onMatch(std::list<AST::node*> t_ASTnodes) {
	std::list<node*>::iterator t_cursor = t_ASTnodes.begin();
	std::list<node*>::iterator t_further = t_ASTnodes.begin();
	byte_code::data::type::container::interface*	_type = NULL;
	std::string					_syntax;
	node::syntax					_file_syntax((*t_cursor)->get_file_syntax());

	if (for_< Match<AST::final::Type> >::organize(t_ASTnodes, t_cursor, t_further))
	  return (t_ASTnodes);


	bool _const = false;
	if (for_< Match<AST::values::Const> >::organize(t_ASTnodes, t_cursor, t_further)) {
	  _syntax = "const ";
	  _const = true;
	}

	if (for_< Match<AST::symbol::Bparenthesis> >::organize(t_ASTnodes, t_cursor, t_further)) {
	  _type = dynamic_cast<AST::final::Type*>(*t_cursor)->getType();
	  _syntax += "(" + (*t_cursor)->get_syntax() + ")";
	  std::advance(t_cursor, 2);
	} else {
	  _type = dynamic_cast<AST::final::ScopedType*>(*t_cursor)->getType();
	  _syntax += (*t_cursor)->get_syntax();
	  std::advance(t_cursor, 1);
	}

	if (_const == true) {
	  _type = new byte_code::data::type::container::derived<byte_code::data::type::derived::const_>(_type);
	}

	while(for_< Match<AST::symbol::Star> >::organize(t_ASTnodes, t_cursor, t_further)) {
	  _type = new byte_code::data::type::container::derived<byte_code::data::type::derived::pointeur_>(_type);
	  _syntax += "*";
	}

	if (for_< Match<AST::symbol::Reference> >::organize(t_ASTnodes, t_cursor, t_further)) {
	  _type = new byte_code::data::type::container::derived<byte_code::data::type::derived::reference_>(_type);
	  _syntax += "*";
	}

	
	std::cout
	  << "type definition, match"
	  << std::endl;
	return { new AST::final::Type(_syntax, _file_syntax, _type) };
      }

    };
  };
};
