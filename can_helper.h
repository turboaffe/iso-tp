
#ifndef CAN_HELPER_H
#define CAN_HELPER_H
#include <iostream> 
#include <string> 
#include <sstream> 

#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

typedef struct can_frame_ts {
    struct can_frame frame_rd;
    struct timeval tv;
} can_frame_ts;



class CanIf {

public:
	void connect();
    int read_if(can_frame_ts* cf_ts);
    int write_if(can_frame_ts* cf_ts);
    std::string port = "vcan0";
    
    CanIf(const std::string& can_if) : port(can_if) {  }

private:
    int soc;

    struct ifreq ifr;
    struct sockaddr_can addr;

};
#endif
