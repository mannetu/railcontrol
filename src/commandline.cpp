#include "commandline.h"

#include <iostream>
#include <vector>
#include "railroad.h"


void console(std::vector<Turnout>& turnout, std::vector<Sign>& sign) 
{
  std::cout << "\nEnter instructions: \n";   
  int x = 1;
  while(x) 
  {
    if(!terminal_input(turnout, sign))
    {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      x = 1;
    }
    else 
      x = 0;
  }
}


//------------------------------------------------------------------
// Terminal input

int terminal_input(std::vector<Turnout>& turnout, std::vector<Sign>& sign)
{
  std::cout << ">> ";

  char type;
  std::cin >> type;
  switch (type)
  {
  case 'w': case 's':
    break;
  case 'q':
    return 1;
  case 'c': 
  	check_status(turnout, sign);
  	return 0;
  case 'r':
    report_status(turnout, sign);
    return 0;
  default:
    std::cout << "type unknown\n";
    return 0;
  }

  unsigned int number;
  std::cin >> number;
  if (!std::cin) {
    std::cout << "no part number\n";
    return 0;
  }

  if ((type == 'w') & ((number < 0) | (number > turnout.size()-1))) {
    std::cout << "no turnout " << number << "\n";
    return 0;
  }

  if ((type == 's') & ((number < 0) | (number > sign.size()-1))) {
    std::cout << "no signal " << number << "\n";
    return 0;
  }

  char instruction;
  std::cin >> instruction;
  if (instruction == 'r') 
  {
    if (type == 'w') 
    {
      std::cout << "Weiche '" << turnout.at(number).get_label() << "' auf "
        << turnout.at(number).get_state() << std::endl;
    }    
    if (type == 's') 
    {
      std::cout << "Signal '" << sign.at(number).get_label() << "' auf "
        << sign.at(number).get_state() << std::endl;
    }
    return 0;
  }

  if ((instruction == '#') | (instruction == ',')) {
    int new_state;
    std::cin >> new_state;
    if (!std::cin) {
      std::cout << "state unknown\n";
      return 0;
    }
    switch (type) {
      case 'w':
        if ((new_state < 0) | (new_state > 1)) {
          std::cout << "turnout state not possible\n";
          return 0;
        }
        turnout.at(number).set_state(new_state);
        break;
      case 's':
        if ((new_state < 0) | (new_state > 3)) {
          std::cout << "signal state not possible\n";
          return 0;
        }
        sign.at(number).set_state(new_state);
        break;
    }
    return 0;
  }
  std::cout << "instruction unknown\n";
  return 0;
}

/*------------------------------------------------------------------
// Output functions for code development


void report_status(std::vector<Turnout>& turnout, std::vector<Sign>& sign) 
{
  std::cout << "Report Status..\n";
 
  for (unsigned int i = 0; i < turnout.size(); i++) 
  {
    std::cout << "Weiche " << std::dec << turnout.at(i).get_number() << " | " 
    << turnout.at(i).get_label() << "\t| State " << turnout.at(i).get_state()  
    << "\n";
  }
 
  for (unsigned int i = 0; i < sign.size(); i++)
  {
    std::cout << "Signal " << std::dec << sign.at(i).get_number() << " | " 
    << sign.at(i).get_label() << "\t| State " << sign.at(i).get_state() << "\n";
  }
}

*/
