#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "railroad.h"
#include <vector>


void console(std::vector<Turnout>& turnout, std::vector<Sign>& sign);


//------------------------------------------------------------------
// Terminal input

int terminal_input(std::vector<Turnout>& turnout, std::vector<Sign>& sign);

/*------------------------------------------------------------------
// Output functions for code development

void report_status(std::vector<Turnout>& turnout, std::vector<Sign>& sign);
*/

#endif
