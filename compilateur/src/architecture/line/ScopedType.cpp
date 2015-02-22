#include <iostream>
#include "architecture/ASTgrammar.hpp"

# include "data/derived_types.hh"
# include "exception/syntax.hh"

namespace ctvscript {
  namespace AST {
    namespace tree {
      /*
       * Line:: Scoped Type
       */
      std::list<AST::node*> ScopedType::onError(std::list<AST::node*> t_list) {
	std::cout
	  << "scoped id, error"
	  << std::endl;
	return (t_list);
      }

      std::list<AST::node*> ScopedType::onMatch(std::list<AST::node*> t_ASTnodes) {
	std::list<node*>::iterator t_cursor = t_ASTnodes.begin();
	std::list<node*>::iterator t_further = t_ASTnodes.begin();
	byte_code::data::type::wrapper*			_type;
	AST::node*					_previous_scope = *t_cursor;
	node::syntax					_file_syntax(_previous_scope->get_file_syntax());
	std::string					_syntax = _previous_scope->get_syntax();

	/*
	 * Test if already transformed
	 */
	if (for_< Match<AST::final::ScopedType> >::organize(t_ASTnodes, t_cursor, t_further))
	  return (t_ASTnodes);

	/*
	 * get primary scope/type (pscope/type (:: others))
	 */
	_type = byte_code::data::type::current_context; 
	while (_type && !_type->exist(_previous_scope->get_syntax())) {
	  _type = _type->getUp();
	}
	if (_type == NULL)
	  throw exception::syntax::undefined_type(_previous_scope->get_file_syntax(), _previous_scope->get_syntax());
	_type = _type->at(_previous_scope->get_syntax());
	++t_cursor;

	/*
	 * recursion in scope to get the final type
	 */
	while (for_< Match<AST::operands::ScopeResolution> >::organize(t_ASTnodes, t_cursor, t_further)) {
	  _syntax = _syntax + "::" + (*t_cursor)->get_syntax();
	  if (!_type->is_scope())
	    throw exception::syntax::non_descopable_type(_previous_scope->get_file_syntax(), _previous_scope->get_syntax());
	  if (!_type->exist((*t_cursor)->get_syntax()))
	    throw exception::syntax::undefined_type((*t_cursor)->get_file_syntax(), (*t_cursor)->get_syntax());
	  _type = _type->at((*t_cursor)->get_syntax());
	  _previous_scope = *t_cursor;
	  ++t_cursor;
	}

	/*
	 * create & return a final AST node
	 */
	return { new AST::final::ScopedType(_syntax, _file_syntax, _type->get_type()->deep_copy()) };
      }
    };
  };
};
