#ifndef RAILROAD_H
#define RAILROAD_H
/*

  railroad.h

*/

#include <string>
#include <vector>
class Canbus;

//-------------------------------------------------------------
// CAN address masks
//-------------------------------------------------------------
const int ADDR_TURN = 0x400; // Turnout Set
const int ADDR_TUFB = 0x500; // Turnout Feedback
const int ADDR_SIGN = 0x600; // Signal Set

//-------------------------------------------------------------
// Railroad
//-------------------------------------------------------------
class Railroad {
  public:
    virtual int set_state(int state) = 0;
    virtual int get_state() = 0;
    virtual std::string get_label() = 0;
		int get_canid() {return m_canid;};
    int get_number() {return m_nr;};
  protected:
    Railroad(Canbus& bus)
    : m_bus(bus),
      m_node(0),
      m_channel(0),
      m_canid(0),
      m_state(0) { };
    Canbus& m_bus;
    std::string m_label;
    int m_nr;
    int m_node;
    int m_channel;
    int m_canid;
    int m_state;
};

//-------------------------------------------------------------
// Turnouts
//-------------------------------------------------------------
class Turnout : public Railroad {
  public:
    Turnout(Canbus& bus, int nr, std::string label, int node, int channel);
		int switch_state(int state);
    int set_state(int state);
    int check_state();
    int get_state() {return m_state;};
    std::string get_label() {return m_label;};
};

//-------------------------------------------------------------
// Signals
//-------------------------------------------------------------
class Sign : public Railroad {
  public:
    Sign(Canbus& bus, int nr, std::string label, int node, int channel);
		int switch_state(int state);
    int set_state(int state);
    int get_state() {return m_state;};
    std::string get_label() {return m_label;};
};


//------------------------------------------------------------------
// Helper functions 

void check_status(std::vector<Turnout>& turnout, std::vector<Sign>& sign);
void report_status(std::vector<Turnout>& turnout, std::vector<Sign>& sign);
int parse_can_msg(const struct can_frame& frame, std::vector<Turnout>& turnout);

#endif // RAILROAD_H
