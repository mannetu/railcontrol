/*********************************************************
* canbus.cpp
*
*
*********************************************************/

#include "canbus.h"
#include "iostream"

Canbus::Canbus(const char* ifname) : m_ifname{ifname}
{
  init();
}

int Canbus::get_frame()
{
  nbytes = read(s, &m_frame, sizeof(struct can_frame));

  if (nbytes < 0)
  {
    //std::cout << "can raw socket read" << std::endl;
    return -1;
  }
  //paranoid check ...
  if (nbytes < abs(sizeof(struct can_frame)))

  {
    std::cout << "read: incomplete CAN frame" << std::endl;
    return -1;
  }
  // Output received message
  std::cout << std::dec << "\n<< Msg received: " << int(m_frame.can_dlc)
    << " Byte\t" << "ID: " << std::hex << std::showbase << m_frame.can_id
    << " || ";
  for (int i = 0; i < m_frame.can_dlc; i++)
  {
    std::cout << int(m_frame.data[i]) << " | ";
  }
  std::cout << std::dec << "\n>> ";
  std::cout.flush();
  return nbytes;
}

int Canbus::output(int canid, int data0)
{
  std::cout << std::hex << std::showbase << "CAN: " << canid << " | " << data0;
  m_frame.can_id = canid;
  m_frame.can_dlc = 1;
  m_frame.data[0] = data0;
  return send_frame();
}

int Canbus::send_frame()
{
  nbytes = write(s, &m_frame, sizeof(struct can_frame));
  std::cout << std::dec << " [wrote " << nbytes << "bytes]\n" << std::endl;
  return nbytes;
}

int Canbus::init() {
  std::cout << "\nSetting up CAN controller ... " ;
  s = socket(PF_CAN, SOCK_RAW | SOCK_NONBLOCK, CAN_RAW);
  if (s < 0)
  {
    perror("Error while opening socket");
    return -1;
  }
  strcpy(ifr.ifr_name, m_ifname);
  ioctl(s, SIOCGIFINDEX, &ifr);
  addr.can_family  = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  printf("%s at index %d\n\n", m_ifname, ifr.ifr_ifindex);

  if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    perror("Error in socket bind");
    return -2;
  }
  return 0;
}
