#include "cTVScript.hh"

int test(int, int) { return (0); }

int main() {//  aa a
  cTVScript::primaryLoadable<int> p1("p1");
  cTVScript::stringLoadable s1("s2");
  cTVScript::StaticLoadableFunction<int, int, int> t1("t1", &test);

  return (0);
}
