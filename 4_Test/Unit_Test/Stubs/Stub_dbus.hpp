
#include "gmock/gmock.h"
#include <assert.h> 
#include "gnssDBus.hpp" 

namespace Mock 
{
    class Mock_MockBasicGnssDbus: 
        public sdbus::ProxyInterfaces<com::idneo::ublox_proxy> 
    {
        public:
        static Mock::Mock_MockBasicGnssDbus *instance; 
        
        Mock_MockBasicGnssDbus(  ): 
            sdbus::ProxyInterfaces<com::idneo::ublox_proxy>(std::move("destination"), std::move("object_path"))
        {
            assert((( Mock::Mock_MockBasicGnssDbus::instance == NULL ) && "You have several mock objects of the type Mock_stdlib. Please remove the duplicated object."));
            instance = this;
        }

        ~Mock_MockBasicGnssDbus(void) 
        {
            instance = NULL;
        }

         
        MOCK_METHOD1( registerDBusListener, int ( const std::shared_ptr<Gnss::IDbusListener>& listener ));
        MOCK_METHOD1( unRegisterDBusListener, int ( const std::shared_ptr<Gnss::IDbusListener>& listener ));
        MOCK_METHOD0( getVersion, std::string  ( void ));
        
 
    };
} 
#define MOCK_ASSERT_GNSSS_DBUS assert((( Mock::Mock_MockBasicGnssDbus::instance != NULL ) && "UT error: You have to add a mock object of type Mock_basicString to your test class."));

Mock::Mock_MockBasicGnssDbus *Mock::Mock_MockBasicGnssDbus::instance = NULL;


/**
 * @brief Construct a new Gnss:: Gnss D Bus:: Gnss D Bus object
 * 
 * @param destination 
 * @param object_path 
 */
Gnss::GnssDBus::GnssDBus(std::string destination, std::string object_path): 
    sdbus::ProxyInterfaces<com::idneo::ublox_proxy>(std::move(destination), std::move(object_path))
{ 
}

/**
 * @brief Destroy the Gnss:: Gnss D Bus:: Gnss D Bus object
 * 
 */
Gnss::GnssDBus::~GnssDBus()
{  
}

bool Gnss::GnssDBus::registerDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener)
{
    MOCK_ASSERT_GNSSS_DBUS
    return Mock::Mock_MockBasicGnssDbus::instance->registerDBusListener(listener);
}
bool Gnss::GnssDBus::unRegisterDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener)
{
    MOCK_ASSERT_GNSSS_DBUS
    return Mock::Mock_MockBasicGnssDbus::instance->unRegisterDBusListener(listener);

}

template <>
std::string sdbus::ProxyInterfaces<com::idneo::ublox_proxy>::getVersion()
{
    MOCK_ASSERT_GNSSS_DBUS
    return Mock::Mock_MockBasicGnssDbus::instance->getVersion(); 
}  