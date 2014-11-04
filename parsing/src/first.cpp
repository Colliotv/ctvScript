#include <fstream>

#include "parsing/parser.hh"

int main(int n, char** av) {
  ctvscript::parser::language_parser py;
  std::string file;
  std::string line;

  if (n > 1) {
    std::fstream _file(av[1]);
    do {
      getline(_file, line);
      file += line + "\n";
    } while (!_file.eof());
    py.parse(file);
  }
}
