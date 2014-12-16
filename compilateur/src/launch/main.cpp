#include <iostream>

# include "syntax/ASTparser.h"
int main() {
  int retval = 0;
  try {
    ctvscript::parser::ASTparser::parse("var var'a' -- / * var var variable1 var + var \"vaar\"				");
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
