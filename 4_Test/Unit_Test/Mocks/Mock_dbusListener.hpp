
#include "gmock/gmock.h"
#include <assert.h>  
#include "gmock/gmock.h" 
   
#include "gnssDBus.hpp"

#ifndef MOCK_DBUSLISTENER_H
#define MOCK_DBUSLISTENER_H

namespace Mock 
{
    class Mock_MockBasicGnssDbusListener: public Gnss::IDbusListener
    {
        public:
        void onDbusNmeaFrames(const std::string& value)
        {
            
        }

        void onDbusUbloxState(const std::string& value)
        {
            
        }
        
        Mock_MockBasicGnssDbusListener(void) 
        { 
        }

        ~Mock_MockBasicGnssDbusListener(void) { 
        }
    };
}  
 
 
#endif
