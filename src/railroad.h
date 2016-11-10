#ifndef RAILROAD_H
#define RAILROAD_H

#include <string>
class Canbus;

//-------------------------------------------------------------
// CAN address masks

const int ADDR_TURN = 0x400; // Turnout Set
const int ADDR_TUFB = 0x500; // Turnout Feedback
const int ADDR_SIGN = 0x600; // Signal Set

//-------------------------------------------------------------
// Railroad

class Railroad {
  public:
  virtual int set(int state) = 0;

  protected:
  Railroad(Canbus& bus) : m_bus(bus), m_node(0), m_nr(0),
      m_canid(0), m_state(0) {};
  Canbus& m_bus;
  std::string m_label;
  int m_node;
  int m_nr;
  int m_canid;
  int m_state;
};

//-------------------------------------------------------------
// Turnouts

class Turnout : public Railroad {
  public:
  Turnout(Canbus& bus, std::string label, int node, int nr);
  int set(int state);
};

//-------------------------------------------------------------
// Signals

class Sign : public Railroad {
  public:
  Sign(Canbus& bus, std::string label, int node, int nr);
  int set(int state);
};

#endif
