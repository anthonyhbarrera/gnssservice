
#include "gmock/gmock.h"
#include <assert.h>  
 #include "gmock/gmock.h" 
 
#include "gnssService.hpp" 
#include "GnssUdp.hpp"
#ifndef MOCK_GNSSSERVICE_H
#define MOCK_GNSSSERVICE_H

namespace Mock 
{
    class Mock_MockBasicGnssService
    {
        public:
        static Mock::Mock_MockBasicGnssService *instance; 
        
        Mock_MockBasicGnssService(void) 
        {
            assert((( Mock::Mock_MockBasicGnssService::instance == NULL ) && "You have several mock objects of the type Mock_stdlib. Please remove the duplicated object."));
            instance = this;
        }

        ~Mock_MockBasicGnssService(void) 
        {
            instance = NULL;
        }

        
        MOCK_METHOD2( createSocket, int (const std::shared_ptr<Gnss::IUdp> &_gnss_udp,
                                        const std::shared_ptr<Gnss::GnssIParseNmea> _gnss_nemaFrames));
        MOCK_METHOD0( closeSocket, int ( void));
 
    };
} 
#define MOCK_ASSERT_GNSSS_SERVICE assert((( Mock::Mock_MockBasicGnssService::instance != NULL ) && "UT error: You have to add a mock object of type Mock_basicString to your test class."));

Mock::Mock_MockBasicGnssService *Mock::Mock_MockBasicGnssService::instance = NULL;


Gnss::GnssService::GnssService()
{

}

Gnss::GnssService::~GnssService()
{

}

int Gnss::GnssService::createSocket(const std::shared_ptr<Gnss::IUdp> &_gnss_udp,
                                    const std::shared_ptr<Gnss::GnssIParseNmea> _gnss_nemaFrames)
{
    MOCK_ASSERT_GNSSS_SERVICE
    return Mock::Mock_MockBasicGnssService::instance->createSocket(_gnss_udp, _gnss_nemaFrames);
}

int Gnss::GnssService::closeSocket(void)
{
    MOCK_ASSERT_GNSSS_SERVICE
    return Mock::Mock_MockBasicGnssService::instance->closeSocket();
}

void Gnss::GnssService::onDbusNmeaFrames(const std::string& value)
{

}

void Gnss::GnssService::onDbusUbloxState(const std::string& value)
{

}

#endif //MOCK_GNSSSERVICE_H
