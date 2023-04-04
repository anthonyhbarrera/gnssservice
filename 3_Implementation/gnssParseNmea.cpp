/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief GNSS class
* @file gnssParseNmea.cpp
*******************************************************************************/
 
#include <thread> 
#include <iomanip>
#include <iostream>
#include <string>
#include <iomanip>
#include "gnssParseNmea.hpp"    
#include "syslog.h"
/* ----------------------------- Macro Defines ------------------------------ */   

/* -------------------------------- Defines --------------------------------- */  

#define GNRMC_STRING "GNRMC"
#define GNGGA_STRING "GNGGA"


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
 
/**
 * @brief Function to calculate the NMEA Checksum
 * 
 * @param s 
 * @return std::uint8_t 
 */
std::uint8_t Gnss::GnssParseNmea::calculateChecksum(std::string s)
{
	uint8_t checksum = 0; 
    
    for(int i = 0; i < (int)(s.length()); i++)
    {
		checksum = checksum ^ s[i];
	}
 
	return checksum;
}

/**
 * @brief 
 * 
 * @param value     Input String
 * @return true     Valid NMEA Frame
 * @return false    Invalid NMEA Frame
 */
bool Gnss::GnssParseNmea::parseNmea(const std::string& value)
{ 
    std::string NewString;
    std::string readName;
    bool isValidFrame = true;
	
	if (value.empty())
    { 
        std::cerr<<"Blank string -- Skipped processing."<<std::endl;
        isValidFrame = false;
	}
    else
    { 
        /* If there is a newline at the end (we are coming from the byte reader*/
        if ( *(value.end()-1) == '\n')
        {
            if (*(value.end() - 2) == '\r')
            {	/* if there is a \r before the newline, remove it.  */
                NewString = value.substr(0, value.size() - 2);
            }
            else
            { 
                NewString = value.substr(0, value.size()-1);
            }
        }
        else
        {
            NewString = value;
        }
        
        
        /* Looking for index of last '$'    */
        size_t startbyte = 0;
        size_t dollar = NewString.find_last_of('$');
        if (dollar == std::string::npos)
        { 
            /* No dollar sign... INVALID!   */
            isValidFrame = false;
        }
        else
        {
            startbyte = dollar;
        }


        /* Get rid of data up to last'$'    */
        if(isValidFrame == true)
        {
            NewString = NewString.substr(startbyte + 1);
        }
        else
        {

        }
        
        /* Look for checksum    */
        size_t checkstri = NewString.find_last_of('*');
        bool haschecksum = checkstri != std::string::npos; 
        if (haschecksum && isValidFrame)
        {
            /* A checksum was passed in the message, so calculate what we expect to see */
            std::uint8_t calculatedChecksum = calculateChecksum(NewString.substr(0, checkstri));
 
            
            std::uint8_t endString = NewString.size();
            std::string readCrcStr = NewString.substr(checkstri+1,endString);
            std::uint8_t readChecksum  = (uint8_t)std::stoi( readCrcStr.c_str(),nullptr,16);
 
            if(readChecksum != calculatedChecksum)
            {
                isValidFrame = false;
            }
            else
            {
                
            }
        }
        else
        {
            /* No checksum is only a warning because some devices allow sending data with no checksum.  */
        }

        /* Handle comma edge cases */

        if(isValidFrame)
        {
            size_t comma = NewString.find(',');
            if (comma == std::string::npos)
            {		
                /* comma not found, but there is a name... */
                isValidFrame = false; 
            }
            else if (comma == 0)
            {
                /* "$," case - no name  */
                isValidFrame = false;

            }
            else
            {
                isValidFrame = true;
                readName = NewString.substr(0, comma);	
            } 
        }
        else
        {
            /*  MISRA MANDATORY ELSE  */
        }
    }

    if(isValidFrame)
    {
        if(readName.compare(GNRMC_STRING) == 0)
        {
            nmea_GNRMC_frame = value;
        }
        else if(readName.compare(GNGGA_STRING) == 0)
        {
            nmea_GNGGA_frame = value;
        }
        else
        {
            /*  Not store frame */
        }
    }
    else
    { 
        /*  Do nothing */
    }

    return isValidFrame;
}

/**
 * @brief 
 * 
 */
void Gnss::GnssParseNmea::publishSyslogNmea(void)
{
    if(nmea_GNGGA_frame.size() > 0)
    {   
        syslog (LOG_INFO, "%s", nmea_GNGGA_frame.c_str());
    }
    else
    {
        /*  Do nothing */
    }

    if(nmea_GNRMC_frame.size() > 0)
    {   
        syslog (LOG_INFO, "%s", nmea_GNRMC_frame.c_str());
    }
    else
    {
        /*  Do nothing */
    
    }
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Gnss::GnssParseNmea::getGNRMCFrame(void)
{
    return nmea_GNRMC_frame;
}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string Gnss::GnssParseNmea::getGNGGAFrame(void)
{
    return nmea_GNGGA_frame;
}
