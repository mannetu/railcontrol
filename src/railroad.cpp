#include "railroad.h"
#include "iostream"
#include "canbus.h"


//-------------------------------------------------------------
// Turnouts

Turnout::Turnout(Canbus& bus, std::string label, int node, int nr) : Railroad(bus)
{
  m_label = label;
  m_node = node;
  m_nr = nr;
  m_canid = (ADDR_TURN | (m_node << 4) | m_nr);
  m_state = 0;
  std::cout << "Turnout\t'" << m_label << std::hex << std::showbase
            << "'\t Node: " << m_node << "  Nr: " << m_nr
            << "\tCAN-ID: " << m_canid << "\n";
}

int Turnout::set(int state)
{
  m_state = state;
  std::cout << "\nTurnout '" << m_label << " auf " << m_state << std::endl;
  m_bus.output(m_canid, m_state);
  return 0;
}

//-------------------------------------------------------------
// Signals

Sign::Sign(Canbus& bus, std::string label, int node, int nr) : Railroad(bus)
{
  m_label = label;
  m_node = node;
  m_nr = nr;
  m_canid = (ADDR_SIGN | (m_node << 4) | m_nr);
  m_state = 0;
  std::cout << "Signal\t'" << m_label << std::hex << std::showbase
            << "'\t Node: " << m_node << "  Nr: " << m_nr
            << "\tCAN-ID: " << m_canid << "\n";
}

int Sign::set(int state)
{
  m_state = state;
  std::cout << "\nSignal '" << m_label << " auf " << m_state << std::endl;
  m_bus.output(m_canid, m_state);
  return 0;
}
