#include <type_traits>
#include <iostream>

#include "cTVScript.hh"

static int toto = 0;

class A : public cTVScript::Loadable{
public:
  A() : Loadable("A") {}
  int test(int, int) { return (toto); }
};
int main() {//  aa a
  cTVScript::primaryLoadable<int> p1("p1");
  cTVScript::stringLoadable s1("s2");
  auto t1 = cTVScript::makeMethodeLoadable("t1", &A::test);
  cTVScript::Context::addObject(t1);

  return (0);
}
