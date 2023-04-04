
#include "gmock/gmock.h"
#include <assert.h>  
 
#include <thread> 
#include <iomanip>
#include <iostream>
#include <string>
#include <iomanip>
#include "gnssParseNmea.hpp"    
/* ----------------------------- Macro Defines ------------------------------ */   

/* -------------------------------- Defines --------------------------------- */  
 


/**
 * @brief Construct a new Gnss:: Gnss Parse Nmea:: Gnss Parse Nmea object
 */
Gnss::GnssParseNmea::GnssParseNmea()
{     
    
}

/**
 * @brief Destroy the Gnss:: Gnss Parse Nmea:: Gnss Parse Nmea object
 */
Gnss::GnssParseNmea::~GnssParseNmea()
{ 
}
 
  


bool Gnss::GnssParseNmea::parseNmea(const std::string& value)
{
     
    bool isValidFrame = true;
	 

    return isValidFrame;
}


std::string Gnss::GnssParseNmea::getGNRMCFrame(void)
{
    return "";
}

std::string Gnss::GnssParseNmea::getGNGGAFrame(void)
{
    return "";
}

void Gnss::GnssParseNmea::publishSyslogNmea(void)
{
    
}