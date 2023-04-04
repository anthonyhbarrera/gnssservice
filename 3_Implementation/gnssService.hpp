/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief GNSS  class
* @file gnssService.hpp
*******************************************************************************/

#ifndef GNSSSERVICE_H
#define GNSSSERVICE_H


/* -------------------------------- Includes -------------------------------- */ 
#include <boost/circular_buffer.hpp> 
#include <memory>
#include "GnssIUdp.hpp" 
#include "gnssDBus.hpp"
#include "gnssIParseNmea.hpp"

#define DEBUG_GNSS_SERVICE 0
namespace Gnss {

/* -------------------------------- Defines --------------------------------- */


/* ------------------------------- Data Types ------------------------------- */
 
/* ------------------------------- Prototypes ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

/* -------------------------------- Routines -------------------------------- */
class GnssService:
    public Gnss::IDbusListener
{
    private:    
        /**
         * @brief Allocation of GNSS UDP class
         */
        std::shared_ptr<Gnss::IUdp> gnss_udp;
        std::shared_ptr<Gnss::GnssIParseNmea> gnss_nemaFrames;
    public:
        GnssService();
        ~GnssService(); 
        int createSocket(   const std::shared_ptr<Gnss::IUdp> &_gnss_udp,
                            const std::shared_ptr<Gnss::GnssIParseNmea> _gnss_nemaFrames);
        int closeSocket(void);
        void onDbusNmeaFrames(const std::string& value);    
        void onDbusUbloxState(const std::string& value);
};
}
#endif
