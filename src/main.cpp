/*********************************************************
* Railcontrol
* main.cpp
*
*********************************************************/

#include <iostream>
#include <vector>
#include <thread>
#include "railroad.h"
#include "canbus.h"
#include "commandline.h"
#include "gleisstellbild.h"


int main(int argc, char *argv[])
{
  std::cout
  << "****************************************************\n"
  << "*           Bruno's Railcontrol System             *\n"
  << "*                    v0.1                          *\n"
  << "****************************************************\n\n";

  // Railroad Setup
  Canbus railbus{"can0"};
  
  std::cout << "Railroad layout..\n\n";

  std::vector<Turnout> turnout;
  turnout.push_back({railbus, 0, "Bahnhof-West", 0, 0});
  turnout.push_back({railbus, 1, "Bahnhof-Ost", 0, 1});
  turnout.push_back({railbus, 2, "Abstellgleis", 2, 1});
  turnout.push_back({railbus, 3, "Bergbahn", 3, 0});

  std::vector<Sign> sign;
  sign.push_back({railbus, 0, "Bhf-Ein-West", 2, 2});
  sign.push_back({railbus, 1, "Bhf-Ein-Ost", 0, 0});

  
  // User Interface
  if (argc>1 && (!strcmp("-g", argv[1]))) // GUI
  {  
    auto app = Gtk::Application::create("org.gtkmm.example");
    GleisStellBild gsb(railbus, turnout, sign);
    //Shows the window and returns when it is closed.
    return app->run(gsb);    
  } 
  else // Terminal-UI
  {       
    console(railbus, turnout, sign);
    return 0;
  }
}



