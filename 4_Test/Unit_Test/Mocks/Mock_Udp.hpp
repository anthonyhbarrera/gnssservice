
#include "gmock/gmock.h"
#include <assert.h>  
#include "gmock/gmock.h" 
   
#include "GnssIUdp.hpp" 

#ifndef MOCK_UDP_H
#define MOCK_UDP_H

namespace Mock 
{
    class Mock_MockBasicGnssUdp : public Gnss::IUdp
    {
        public:
        MOCK_METHOD0( createSocket, int ( void )); 
        MOCK_METHOD0( closeSocket, int ( void )); 
        MOCK_METHOD1( send, bool ( const std::string &nmea )); 
    };
}  
 
 
#endif
