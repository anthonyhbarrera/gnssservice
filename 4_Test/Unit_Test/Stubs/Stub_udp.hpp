
#include "gmock/gmock.h"
#include <assert.h> 
#include "GnssUdp.hpp"
#include "GnssIUdp.hpp"
 
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
    int ret = 0; 
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
    return ret_val;
}

/**
 * @brief Function to close the Socket
 * 
 * @return int 
 */
int Gnss::GnssUdp::closeSocket(void)
{
    return 0 ;
}
   