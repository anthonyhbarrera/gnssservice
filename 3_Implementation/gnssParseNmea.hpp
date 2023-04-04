/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief GNSS  class
* @file gnssParseNmea.hpp
*******************************************************************************/

#ifndef GNSSPARSENMEA_H
#define GNSSPARSENMEA_H


/* -------------------------------- Includes -------------------------------- */  
#include "gnssIParseNmea.hpp"
#include <string>

namespace Gnss {

/* -------------------------------- Defines --------------------------------- */


/* ------------------------------- Data Types ------------------------------- */
 
/* ------------------------------- Prototypes ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

/* -------------------------------- Routines -------------------------------- */
class GnssParseNmea:
    public GnssIParseNmea
{
    private:     
        std::uint8_t calculateChecksum(std::string s);
        std::string nmea_GNRMC_frame;
        std::string nmea_GNGGA_frame;
    public:
        GnssParseNmea();
        ~GnssParseNmea();  
        bool parseNmea(const std::string& value); 
        std::string getGNRMCFrame(void);
        std::string getGNGGAFrame(void);
        void publishSyslogNmea(void);
};
}
#endif
