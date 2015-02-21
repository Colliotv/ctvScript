#include <fstream>
#include <iostream>

# include "syntax/ASTparser.h"
# include "architecture/ASTgrammar.h"
int main(int ac, char** av) {
  if (ac != 2) {
    std::cerr
      << "./" << av[0]
      << " script.ctv"
      << std::endl;
    return (-1);
  }

  std::fstream _script(av[1]);

  {
    int retval = 0;
    try {
      std::list<ctvscript::AST::node*> nodeList;
      ctvscript::parser::ASTparser::parse("def const(const toto::tamere()) ouioui(int toto);", nodeList);
      launch_grammar(nodeList);
    } catch (const std::logic_error& e) {
      retval = 1;
      std::cout
	<< std::endl
	<< "Syntax Error:"
	<< std::endl << e.what()
	<< std::endl;
    }
    return (retval);
  }

}
