/*
 * railroad.cpp
 *
 */

#include "railroad.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "canbus.h"

//-------------------------------------------------------------
// Turnouts
//-------------------------------------------------------------
Turnout::Turnout(Canbus& bus, int nr, std::string label, int node, int channel) : Railroad(bus)
{
  m_nr = nr;
  m_label = label;
  m_node = node;
  m_channel = channel;
  m_canid = (ADDR_TURN | (m_node << 4) | m_channel);
  m_state = 0;
  std::cout << "Weiche " << std::dec << m_nr << " | " << m_label
            << "\t| Node " << m_node
            << " Ch " << m_channel << std::hex << std::showbase
            << "\t| Id " << m_canid << "\n";
}



int Turnout::switch_state(int state)
{
  std::cout << "\nTurnout \'" << m_label << "\' auf " << std::dec << m_state << "\n";
  m_bus.output(m_canid, m_state);
	while (m_state != state) 
	{
	  std::cout << "."; std::cout.flush();
	  std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
  std::cout << "Weiche " << "geschaltet\n";
  std::cout.flush();
  return 0;
}


int Turnout::set_state(int state)
{
  m_state = state;
  return 0;
}

int Turnout::check_state()
{
  return  m_bus.output(m_canid, 0xFF);
}

//-------------------------------------------------------------
// Signals
//-------------------------------------------------------------
Sign::Sign(Canbus& bus, int nr, std::string label, int node, int channel) : Railroad(bus)
{
  m_nr = nr;
  m_label = label;
  m_node = node;
  m_channel = channel;
  m_canid = (ADDR_SIGN | (m_node << 4) | m_channel);
  m_state = 0;
  std::cout << "Signal " << m_nr << " | " << m_label << std::dec
            << "\t| Node " << m_node
            << " Ch " << m_channel << std::hex << std::showbase
            << "\t| Id " << m_canid << std::dec << "\n";
}


int Sign::set_state(int state)
{
  m_state = state;
  std::cout << "\nSignal \'" << m_label << "\' auf " << std::dec << m_state << "\n";
  m_bus.output(m_canid, m_state);
  return 0;
}


//-------------------------------------------------------------
// Helper functions
//-------------------------------------------------------------


void check_status(std::vector<Turnout>& turnout, std::vector<Sign>& sign)
{
  std::cout << "Request status..\n";
 
  for (unsigned int i = 0; i < turnout.size(); i++) 
  {
    turnout.at(i).check_state(); 
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  report_status(turnout, sign);
}


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


int parse_can_msg(const struct can_frame& frame, std::vector<Turnout>& turnout)  
{
	if (((frame.can_id & 0xF00) ^ ADDR_TUFB) == 0)
	{
		for (unsigned int i = 0; i < turnout.size(); i++) 
		{
		  if (turnout.at(i).get_canid() == int(((frame.can_id & 0xFF) | ADDR_TURN)))
		  {
  		  turnout.at(i).set_state(frame.data[0]);
  		  return 0; 
		  }
		};
	}


  std::cout << "id not found\n";
  return -1; 		  
}


