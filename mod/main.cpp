#include "Mod.h"
#include <iostream>

using namespace std;

int main() {
  Mod::set_modulus(101);
  Mod a(LONG_MAX/2);
  a = a.pwr(0);
  cout << a << endl;
}
