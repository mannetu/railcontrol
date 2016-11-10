#include <iostream>
#include "railroad.h"
#include "canbus.h"
//class Canbus;

int main()
{
  Canbus railbus{"vcan0"};

  Turnout turnout{railbus, "Bahnhof-Gleis2-Ost", 1, 1};
  Sign sign{railbus, "Bahnhof-Einfahrt-West", 2, 2};

  turnout.set(1);
  sign.set(2);

  while(1) railbus.get_frame();

  return 0;
}
