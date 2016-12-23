#ifndef CANBUS_H
#define CANBUS_H
/*
 
  canbus.h

*/

#include <string>
// Libraries for SocketCAN
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
//-------------------------------------------------------------
class Canbus
{
public:
  // Constructor. Opens and binds socket to CAN controller
  Canbus(const char* ifname); 

  // sends msg with id and data byte 0. Returns number of send bytes
  int output(int id, int state);  
  
  /* checks if msg is available, stores frame and returns number of 
     received bytes.  */
  int is_can_msg(); 
  
  // returns frame received by call of is_can_msg();
  can_frame get_frame(); 

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
