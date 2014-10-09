#include <type_traits>
#include <iostream>

#include "cTVScript.hh"

int main() {
  cTVScript::primaryLoadable<int> a ("a");
  cTVScript::primaryLoadable<double> b ("b");
}
