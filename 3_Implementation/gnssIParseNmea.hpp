/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief GNSS  class
* @file gnssParseNmea.hpp
*******************************************************************************/

#ifndef GNSSIPARSENMEA_H
#define GNSSIPARSENMEA_H


/* -------------------------------- Includes -------------------------------- */ 
#include <boost/circular_buffer.hpp> 
#include <memory> 
#include <string>


namespace Gnss {

/* -------------------------------- Defines --------------------------------- */


/* ------------------------------- Data Types ------------------------------- */
 
/* ------------------------------- Prototypes ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

/* -------------------------------- Routines -------------------------------- */
class GnssIParseNmea
{ 
    public: 
        virtual bool parseNmea(const std::string& value) = 0; 
        virtual std::string getGNRMCFrame(void) = 0;
        virtual std::string getGNGGAFrame(void) = 0;
};
}
#endif
