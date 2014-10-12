#include <type_traits>
#include <iostream>

#include "cTVScript.hh"

static int helper = 0;

int f1() {
  return (0);
}

int f2(int, double, char) {
  return (0);
}

int& f3(int, double, char*){
  return (helper);
}

int main() {
  auto fn1 = cTVScript::loadable::loadFunction("f", &f1);
  auto fn2 = cTVScript::loadable::loadFunction("f", &f2);
  auto fn3 = cTVScript::loadable::loadFunction("f", &f3);

  delete fn1;
  delete fn2;
  delete fn3;
}
