
#include "gmock/gmock.h"
#include <assert.h> 
#include "gnssDBus.hpp"

namespace Mock 
{
    class Mock_MockBasicDbus: public Gnss::IDbusListener
    {
        public: 
        void onDbusNmeaFrames(const std::string& value)
        {
            
        }

        void onDbusUbloxState(const std::string& value)
        {
            
        }
        
        Mock_MockBasicDbus(void) 
        { 
        }

        ~Mock_MockBasicDbus(void) { 
        }
 
    };
}


bool Gnss::GnssDBus::registerDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener)
{
    bool retVal = false; 

    return retVal;
}

 
bool Gnss::GnssDBus::unRegisterDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener)
{
    bool retVal = false; 
    
    return retVal;
}