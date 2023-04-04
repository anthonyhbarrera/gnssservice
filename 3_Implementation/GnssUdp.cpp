/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief UDP class for Gnss features for TCU
* @file GnssUdp.cpp
*******************************************************************************/
/* -------------------------------- Includes -------------------------------- */

#include "GnssUdp.hpp"
#include <iostream>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <iomanip> 
 
#if (DEBUG_GNSS_UDP == 1)
#define debugOut std::cout 
#else
#define debugOut 0U && std::cout 
#endif 
     
/* -------------------------------- Defines --------------------------------- */

/* ------------------------------- Data Types ------------------------------- */

/* ------------------------------- Prototypes ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

/* -------------------------------- Routines -------------------------------- */
/**
 * @brief Construct a new Gnss:: I Udp:: I Udp object
 */
Gnss::GnssUdp::GnssUdp()
{

}

/**
 * @brief Destroy the Gnss:: I Udp:: I Udp object
 */
Gnss::GnssUdp::~GnssUdp()
{

}

/**
 * @brief Create socket
 * 
 * @return int Return 0 if the socked has been created correctly
 */
int Gnss::GnssUdp::createSocket( void )
{
    debugOut<<__PRETTY_FUNCTION__<<" "<<std::this_thread::get_id()<<std::endl;
    int ret = 0;
    char netif[] = "bridge0";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if(sockfd < 0)
    {
        std::cerr << "Error: Could not create socket. " << std::endl;
        ret = 1;
    }
    else 
    {
        int opt = 1;
        int sock_op_return = 0;
        sock_op_return = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
        debugOut<<"Sock Ret: "<< sock_op_return<<std::endl;
        memset(&serveraddr, 0, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(50020);
        serveraddr.sin_addr.s_addr =  inet_addr("255.255.255.255");
        sock_op_return = setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, netif, sizeof(netif));
        debugOut<<"Sock Ret: "<< sock_op_return<<std::endl;
    }

    return ret;
}

/**
 * @brief Function to send data throught UDP
 * 
 * @param nmea 
 */
bool Gnss::GnssUdp::send(const std::string &nmea)
{
    bool ret_val = false;
    
    if (sendto(sockfd, nmea.c_str(), nmea.size(), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) 
    {
        std::cerr << "Error: Could not send nmea message to socket. " << std::endl;
        std::cerr << errno << std::endl;
    }
    else 
    {
        /* UDP message send correctly*/ 
        ret_val = true; 
        /* Commented to avoid spam */
        debugOut << nmea << std::endl;
    }

    return ret_val;
}

/**
 * @brief Function to close the Socket
 * 
 * @return int 
 */
int Gnss::GnssUdp::closeSocket(void)
{
    debugOut <<__PRETTY_FUNCTION__<<" "<<std::this_thread::get_id()<<std::endl;
    int ret = close(sockfd);
    return ret ;
}
   
 