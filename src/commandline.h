#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "railroad.h"
#include "canbus.h"
#include <vector>


void console(Canbus& bus, std::vector<Turnout>& turnout, std::vector<Sign>& sign);


//------------------------------------------------------------------
// Terminal input

int terminal_input(std::vector<Turnout>& turnout, std::vector<Sign>& sign);

//------------------------------------------------------------------
// Thread function

void thread_get_frame(Canbus &railbus);


#endif
