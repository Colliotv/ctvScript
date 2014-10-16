#include <iostream>

#include "architecture/instruction.hh"
#include "architecture/line.hh"

int main() {
  cTVScript::parsing::instructions::line l;

  std::cout << l.parse_string("if test ;") << std::endl;
}
