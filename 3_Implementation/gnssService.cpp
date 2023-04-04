/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief GNSS class
* @file gnssService.cpp
*******************************************************************************/
 
#include <thread> 
#include "gnssService.hpp"   
#include "GnssUdp.hpp" 
#include "gnssDBus.hpp"
#include <iomanip>

#if (DEBUG_GNSS_SERVICE == 1)
#define debugOut std::cout 
#else
#define debugOut 0U && std::cout 
#endif 
     
/* ----------------------------- Macro Defines ------------------------------ */   

/* -------------------------------- Defines --------------------------------- */  


/**
* @brief Construct a new Gnss:: Gnss Service:: Gnss Service object 
*/
Gnss::GnssService::GnssService()
{     
    
}

/**
 * @brief Destroy the Gnss:: Gnss Service:: Gnss Service object
 */
Gnss::GnssService::~GnssService()
{ 
}
 
 
/**
 * @brief Function to create all sockets needed for GNSS service.
 * 
 * @return Returns 0 if it has success, otherwise returns 1
 */
int Gnss::GnssService::createSocket(const std::shared_ptr<Gnss::IUdp> &_gnss_udp,
                                    const std::shared_ptr<Gnss::GnssIParseNmea> _gnss_nemaFrames)
{
    debugOut<<__PRETTY_FUNCTION__<<" "<<std::this_thread::get_id()<<std::endl;
    int ret = 0;
    
    if(_gnss_udp.get() != nullptr)
    {
        gnss_udp = _gnss_udp; 
    
        debugOut<<ret<<" Create socket "<< std::endl;

        ret = gnss_udp->createSocket();   
        if(0 != ret)
        {
            /* Error detected creating the UDP socket */
            std::cerr<<"Error detected creating sockets."<<ret <<std::endl;
        } 
        else
        {  
            if(_gnss_nemaFrames.get() != nullptr)
            {
                gnss_nemaFrames = _gnss_nemaFrames;
            }
            else
            {
                ret = -1;
                std::cerr<<"Wrong Input pointer."<<ret <<std::endl;
            }
        }
    }
    else
    {
        /*  Wrong Input pointer */
        ret = -1;
        std::cerr<<"Wrong Input pointer."<<ret <<std::endl;
    }

    return ret;
}

/**
 * @brief 
 * 
 * @param value 
 */
void Gnss::GnssService::onDbusNmeaFrames(const std::string& value)
{   
    if(gnss_udp.get() != nullptr)
    { 
        gnss_udp->send(value);
    }
    else
    { 
        /*  Error, the gnss_udp pointer is null */
    }

    if(gnss_nemaFrames.get() != nullptr)
    {
        gnss_nemaFrames->parseNmea(value);
    }
    else
    {
        /*  Misra mandatory else */
    }
}

/**
 * @brief 
 * 
 * @param value 
 */
void Gnss::GnssService::onDbusUbloxState(const std::string& value)
{
    
}

/**
 * @brief Function to close GNSS Service sockets
 * 
 * @return int 
 */
int Gnss::GnssService::closeSocket(void)
{
    debugOut<<__PRETTY_FUNCTION__<<" "<<std::this_thread::get_id()<<std::endl;
    int ret = 0;
      
    if(gnss_udp.get() != nullptr)
    {
        ret |= gnss_udp->closeSocket(); 
    }
    else
    {
        /*  Error, the gnss_udp pointer is null */
        ret = -1;
    }

    return ret;
}
