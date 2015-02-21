std::list<AST::node*> ScopedType::onError(std::list<AST::node*> t_list) {
  std::cout
    << "scoped id, error"
    << std::endl;
  return (t_list);
}

std::list<AST::node*> ScopedType::onMatch(std::list<AST::node*> t_ASTnodes) {
  std::list<node*>::iterator t_cursor = t_ASTnodes.begin();
  std::list<node*>::iterator t_further = t_ASTnodes.begin();
  const byte_code::data::type::wrapper*		_scope;

  if (byte_code::data::type::current_context->exist((*t_cursor)->get_syntax()))
    _scope = byte_code::data::type::current_context;
  else
    _scope = &byte_code::data::type::table;
  do {
    

  } while (for_< Match<AST::operands::ScopeResolution> >::organize(t_ASTnodes, t_cursor, t_further));
  std::cout
    << "scoped id, match"
    << std::endl;
  return (t_ASTnodes);
}
