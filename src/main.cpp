/*********************************************************
* Railcontrol
* main.cpp
*
*********************************************************/

#include <iostream>
#include <vector>
#include <thread>
//#include <mutex>
#include "railroad.h"
#include "canbus.h"
#include "commandline.h"
#include "gleisstellbild.h"


// Function prototypes
void thread_get_frame(Canbus &railbus);


int main(int argc, char *argv[])
{
  std::cout
  << "****************************************************\n"
  << "*           Bruno's Railcontrol System             *\n"
  << "*                    v0.1                          *\n"
  << "****************************************************\n\n";

  // Define CANbus, turnouts and signals 
  Canbus railbus{"vcan0"};
  
  std::cout << "Define railroad layout..\n\n";

  std::vector<Turnout> turnout;
  turnout.push_back({railbus, 0, "Bahnhof-West", 0, 0});
  turnout.push_back({railbus, 1, "Bahnhof-Ost", 1, 0});
  turnout.push_back({railbus, 2, "Abstellgleis", 2, 1});
  turnout.push_back({railbus, 3, "Bergbahn", 3, 0});

  std::vector<Sign> sign;
  sign.push_back({railbus, 0, "Bhf-Ein-West", 2, 2});
  sign.push_back({railbus, 1, "Bhf-Ein-Ost", 0, 0});

  // Start user interface (GUI or text-based)
  if (argc>1 && (!strcmp("-g", argv[1]))) 
  {  
    // GUI
    auto app = Gtk::Application::create("org.gtkmm.example");
    GleisStellBild gsb(railbus, turnout, sign);
    //Shows the window and returns when it is closed.
    return app->run(gsb);    
  } 
  else 
  {
   // Text user interface
   // Start thread checking for received msges 
    std::thread thread1(thread_get_frame, std::ref(railbus));
    thread1.detach();
  
    // Start input
    console(turnout, sign);
    return 0;
  }
}

void thread_get_frame(Canbus &railbus)
{
  while(1) 
  {
    railbus.get_frame();
    std::chrono
  }
}


