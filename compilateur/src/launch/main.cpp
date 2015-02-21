#include <iterator>
#include <fstream>
#include <iostream>

# include "syntax/ASTparser.h"
# include "architecture/ASTgrammar.h"

# include "exception/syntax.h"

int main(int ac, char** av) {
  if (ac != 2) {
    std::cerr
      << av[0]
      << " script.ctv"
      << std::endl;
    return (-1);
  }

  std::fstream _script(av[1]);

  {
    int retval = 0;
    try {
      std::list<ctvscript::AST::node*> nodeList;
      ctvscript::parser::ASTparser::parse(std::string(std::istreambuf_iterator<char>(_script),
						      std::istreambuf_iterator<char>()),
					  nodeList);
      launch_grammar(nodeList);
    } catch (const ctvscript::exception::syntax::error& e) {
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
