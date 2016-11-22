#include "commandline.h"

#include <iostream>
#include <vector>
#include "railroad.h"


int commandline(std::vector<Turnout>& turnout, std::vector<Sign>& sign)
{
  while(!terminal_input(turnout, sign))
  {
    std::cin.clear();
    std::cin.ignore(1000, '\n');
  }
  return 0;
}

//------------------------------------------------------------------
// Terminal input

int terminal_input(std::vector<Turnout>& turnout, std::vector<Sign>& sign)
{
  std::cout << ">> ";

  char type;
  std::cin >> type;
  switch (type) {
    case 'w': break;
    case 's': break;
    case 'q': return 1;
    case 'r':
    {
      std::cout << "Report Status" << std::endl;
      return 0;
    }
    default:
    {
     std::cout << "type unknown" << std::endl;
     return 0;
    }
  }

  int number;
  std::cin >> number;
  if (!std::cin)
  {
    std::cout << "no part number" << std::endl;
    return 0;
  }

  if ((type == 'w') & ((number < 0) | (number > turnout.size()-1)))
  {
    std::cout << "no turnout " << number << std::endl;
    return 0;
  }

  if ((type == 's') & ((number < 0) | (number > sign.size()-1)))
  {
    std::cout << "no signal " << number << std::endl;
    return 0;
  }

  char instruction;
  std::cin >> instruction;
  if (instruction == 'r')
  {
    std::cout << "REPORT " << type << number << std::endl;
    return 0;
  }

  if (instruction == '#')
  {
    int new_state;
    std::cin >> new_state;
    if (!std::cin)
    {
      std::cout << "state unknown" << std::endl;
      return 0;
    }
    switch (type)
    {
      case 'w':
        if ((new_state < 0) | (new_state > 1))
        {
          std::cout << "turnout state not possible" << std::endl;
          return 0;
        }
        turnout_set(turnout, number, new_state);
        break;
      case 's':
        if ((new_state < 0) | (new_state > 3))
        {
          std::cout << "signal state not possible" << std::endl;
          return 0;
        }
        sign_set(sign, number, new_state);
        break;
    }
    return 0;
  }

  std::cout << "instruction unknown" << std::endl;
  return 0;
}

//------------------------------------------------------------------
// Output functions for code development

int turnout_set(std::vector<Turnout>& turnout, const int nr, const int state)
{
  //std::cout << "Weiche " << nr << " auf " << state << std::endl;
  turnout.at(nr).set_state(state);
  return 0;
}

int sign_set(std::vector<Sign>& sign, const int nr, const int state)
{
  //std::cout << "Signal " << nr << " auf " << state << std::endl;
  sign.at(nr).set_state(state);
  return 0;
}
