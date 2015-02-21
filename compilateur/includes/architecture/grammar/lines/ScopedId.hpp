std::list<AST::node*> ScopedId::onError(std::list<AST::node*> t_list) {
  std::cout
    << "scoped id, error"
    << std::endl;
  return (t_list);
}

std::list<AST::node*> ScopedId::onMatch(std::list<AST::node*> t_ASTnodes) {
  std::cout
    << "scoped id, match"
    << std::endl;
  return (t_ASTnodes);
}
