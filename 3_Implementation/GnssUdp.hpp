/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief UDP class for Gnss features for TCU
* @file GnssUdp.hpp
*******************************************************************************/

#ifndef GNSSUDP_H
#define GNSSUDP_H

/* -------------------------------- Includes -------------------------------- */
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <cstring>
#include <iostream> 
#include "GnssIUdp.hpp"

#define DEBUG_GNSS_UDP  0

namespace Gnss {

/* -------------------------------- Defines --------------------------------- */

/* ------------------------------- Data Types ------------------------------- */

/* ------------------------------- Prototypes ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

/* -------------------------------- Routines -------------------------------- */

class GnssUdp : public IUdp
{
public:
    GnssUdp();
    ~GnssUdp();
    int createSocket(void);
    bool send(const std::string &nmea);
    int closeSocket(void);  
private:
    int sockfd = 0;
    struct sockaddr_in serveraddr;
};
}/* End of namespace Gnss */

#endif /* GNSSUDP_H */
