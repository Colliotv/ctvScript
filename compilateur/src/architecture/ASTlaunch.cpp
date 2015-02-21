#include <iostream>
#include "architecture/ASTgrammar.hpp"

namespace ctvscript {
  namespace AST {

    void launch_grammar(std::list<node*>& t_ASTnodes) {
      std::list<node*>::iterator t_cursor = t_ASTnodes.begin();
      std::list<node*>::iterator t_further = t_ASTnodes.begin();
      if (!for_< tree::Call<AST::tree::line_name::global> >::organize(t_ASTnodes, t_cursor, t_further))
	std::cerr << std::endl << std::endl << std::endl << "fail in grammar structuring!!!!!!" << std::endl;
      else if (t_further == t_ASTnodes.end())
	std::cerr << std::endl << std::endl << std::endl << "success in grammar structuring!!!!!!" << std::endl;
    }


  };
};
