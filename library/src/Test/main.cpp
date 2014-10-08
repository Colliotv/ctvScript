#include <type_traits>
#include <iostream>

#include "cTVScript.hh"

static int toto = 0;

int test(int, int) { return (toto); }

int main() {//  aa a
  cTVScript::primaryLoadable<int> p1("p1");
  cTVScript::stringLoadable s1("s2");
  auto t1 = cTVScript::makeFunctionLoadable("t1", &test);
  std::cout << t1 << std::endl;
  return (0);
}
