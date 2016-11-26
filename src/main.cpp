/*********************************************************
* Railcontrol
* main.cpp
*
*********************************************************/

#include <iostream>
#include <vector>
#include "railroad.h"
#include "canbus.h"
#include "commandline.h"


int main()
{
  std::cout
  << "****************************************************\n"
  << "*           Bruno's Railcontrol System             *\n"
  << "*                    v1.0                          *\n"
  << "****************************************************\n\n";

  Canbus railbus{"vcan0"};

  // Definition of turnouts and signals
  std::cout << "Define railroad layout..\n\n";

  std::vector<Turnout> turnout;
  turnout.push_back({railbus, 0, "Bahnhof-West", 1, 0});
  turnout.push_back({railbus, 1, "Bahnhof-Ost ", 2, 0});
  turnout.push_back({railbus, 2, "Abstellgleis", 1, 1});
  turnout.push_back({railbus, 3, "Bergbahn    ", 3, 0});

  std::vector<Sign> sign;
  sign.push_back({railbus, 0, "Bhf-Ein-West", 2, 2});


  std::cout << "\nEnter instructions: \n";
  while(1)
  {
    if (!commandline(turnout, sign)) break;
    railbus.get_frame();
  }

  //commandline(turnout, sign);

  // Test switching
  // std::cout << "\nSwitching parts..\n";
  // turnout[2].set_state(1);
  // sign[0].set_state(2);

  // Test receiving CAN messages
  //  while(1) railbus.get_frame();

  return 0;
}
