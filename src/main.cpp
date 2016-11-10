#include <iostream>
#include "railroad.h"
#include "canbus.h"
//class Canbus;

int main()
{
  Canbus railbus{"vcan0"};

  std::cout << "Define railroad layout..\n";
  Turnout turnout{railbus, "Bahnhof-Gleis2-Ost", 1, 1};
  Sign sign{railbus, "Bahnhof-Einfahrt-West", 2, 2};

  std::cout << "Switching parts..\n";
  turnout.set(1);
  sign.set(2);

  while(1) railbus.get_frame();

  return 0;
}
