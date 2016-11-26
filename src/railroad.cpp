/*********************************************************
* railroad.cpp
*
*
*********************************************************/
#include "railroad.h"
#include <iostream>
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

int Turnout::set_state(int state)
{
  m_state = state;
  std::cout << "\nTurnout \'" << m_label << "\' auf " << std::dec << m_state << "\n";
  m_bus.output(m_canid, m_state);
  return 0;
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
