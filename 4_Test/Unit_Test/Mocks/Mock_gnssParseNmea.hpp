
#include "gmock/gmock.h"
#include <assert.h>  
#include "gmock/gmock.h" 
   
#include "gnssIParseNmea.hpp" 
#include <string>

#ifndef MOCK_GNSSPARSENMEA_H
#define MOCK_GNSSPARSENMEA_H

namespace Mock 
{
    class Mock_MockBasicGnssParseNmea : public Gnss::GnssIParseNmea
    {
        public:
        Mock_MockBasicGnssParseNmea(void)
        {

        }
        ~Mock_MockBasicGnssParseNmea(void)
        {
            
        }
        MOCK_METHOD0( getGNRMCFrame, std::string ( void )); 
        MOCK_METHOD0( getGNGGAFrame, std::string ( void )); 
        MOCK_METHOD1( parseNmea, bool ( const std::string &value )); 
    };
}  
  
#endif