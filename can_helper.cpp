#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdexcept>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "can_helper.h"

using namespace std;


void CanIf::connect() {


    soc = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if(soc < 0)
    {
        throw std::domain_error("cannot open socket");
    }

    addr.can_family = AF_CAN;
	strcpy(ifr.ifr_name, port.c_str());

    if (ioctl(soc, SIOCGIFINDEX, &ifr) < 0)
    {
        throw std::domain_error("cannot get interface index");
    }

    addr.can_ifindex = ifr.ifr_ifindex;

    fcntl(soc, F_SETFL, O_NONBLOCK);

    if (bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        throw std::domain_error("failed to bind interface");
    }

}


int CanIf::read_if(can_frame_ts* cf_ts) {

    int recvbytes = 0;
    struct timeval timeout = {5, 0};

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(soc, &readSet);

    if (select((soc + 1), &readSet, NULL, NULL, &timeout) >= 0)
    {
	    recvbytes = read(soc, &(cf_ts->frame_rd), sizeof(cf_ts->frame_rd));
	    if(recvbytes)
	    {
	        // get timestamp
	        ioctl(soc, SIOCGSTAMP, &(cf_ts->tv));
	
			return 0;
		}
		else
		{
			return -1;
		}	
	}

}

int CanIf::write_if(can_frame_ts* cf_ts) {

    int nbytes = write(soc, &(cf_ts->frame_rd), sizeof(cf_ts->frame_rd));

    return nbytes;

}


