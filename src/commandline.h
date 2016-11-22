#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include "railroad.h"
#include <vector>


int commandline(std::vector<Turnout>&, std::vector<Sign>&);

//------------------------------------------------------------------
// Terminal input

int terminal_input(std::vector<Turnout>& turnout, std::vector<Sign>& sign);

//------------------------------------------------------------------
// Output functions for code development

int turnout_set(std::vector<Turnout>& turnout, const int nr, const int state);
int sign_set(std::vector<Sign>& sign, const int nr, const int state);


#endif
