#ifndef CANBUS_H
#define CANBUS_H

#include <string>

//-------------------------------------------------------------
// C and SocketCAN libraries
//-------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

//-------------------------------------------------------------
// Canbus
//
//-------------------------------------------------------------
class Canbus
{
public:
  Canbus(const char* ifname);
  int output(int id, int state);
  int get_frame();
private:
  const char* m_ifname;
  struct can_frame m_frame;
  int s;
  struct sockaddr_can addr;
  struct ifreq ifr;
  ssize_t nbytes;
  int init();
  int send_frame();
};

#endif // CANBUS_H
