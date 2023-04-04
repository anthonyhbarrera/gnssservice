/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief UDP class for Gnss features for TCU
* @file GnssUdp.hpp
*******************************************************************************/

#ifndef GNSSIUDP_H
#define GNSSIUDP_H

/* -------------------------------- Includes -------------------------------- */
 
#include <cstring> 
 

namespace Gnss {

/* -------------------------------- Defines --------------------------------- */

/* ------------------------------- Data Types ------------------------------- */

/* ------------------------------- Prototypes ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

/* -------------------------------- Routines -------------------------------- */

class IUdp
{ 
public: 
    virtual int     createSocket(void)              = 0;
    virtual bool    send(const std::string &nmea)   = 0;
    virtual int     closeSocket(void)               = 0;  
};
}/* End of namespace Gnss */

#endif // GNSSIUDP_H
