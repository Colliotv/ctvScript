#include "parsing/parser.hh"

int main() {
  ctvscript::parser::language_parser py;
  std::string file;
  std::string line;

  do {
    getline(std::cin, line);
    file += line;
  } while (!line.empty());
  py.parse(file);
}
