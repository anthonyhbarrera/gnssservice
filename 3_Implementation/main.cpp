/************  Copyright 2004-2017 FICOSA CORPORATIVE ELECTRONICS  ********//**
* @par Language: MISRA C
* @par Framework: Linux
* @par Spec:
* @par Project: Canoo
* @brief Gnss features for TCU  
* @file main.cpp
*******************************************************************************/

/* -------------------------------- Includes -------------------------------- */
 
#include <csignal>
#include <time.h>
#include <syslog.h>
#include "gnssService.hpp"  
#include "gnssDBus.hpp"
#include "GnssUdp.hpp"
#include "gnssParseNmea.hpp"

     
/* -------------------------------- Defines --------------------------------- */

#define LOG_ENABLE_TEST     0
#define DEBUG_GNSS_MAIN     0


#if (DEBUG_GNSS_MAIN == 1)
#define debugOut std::cout 
#else
#define debugOut 0U && std::cout 
#endif 

#define TIME_SYSLOG_PUBLISH_S   ((std::time_t)60)
/* ------------------------------- Data Types ------------------------------- */

/* ------------------------------- Prototypes ------------------------------- */

/* ---------------------------- Global Variables ---------------------------- */

static bool working = true;
/* -------------------------------- Routines -------------------------------- */


#ifdef UNIT_TEST   
std::time_t getTime(void);
#else
std::time_t getTime(void)
{
    return std::time(nullptr);
} 
#endif

/**
 * @brief gnss_signal_handler
 * @param signum
 */
void gnss_signal_handler( int signum )
{
    debugOut << "Interrupt signal (" << signum << ") received." << std::endl;
    working = false;
}

#if LOG_ENABLE_TEST == 1
void currentDateTime(char *_inBuf, bool logFile) 
{
    std::time_t     now = getTime();
    char       buf[80];
    
    /* Visit http://en.cppreference.com/w/cpp/chrono/c/strftime */
    /* for more information about date/time format    */
    if(logFile)
    {   std::strftime(buf, sizeof(buf), "logFiles/logGnssService_%H%M%S.log", std::localtime(&now));
    }
    else
    {   std::strftime(buf, sizeof(buf), "logFiles/errorLogGnssService_%H%M%S.log", std::localtime(&now));

    }
    debugOut << buf << '\n';
    for(std::uint8_t i = 0; i < sizeof(buf); i++)
    {
        _inBuf[i] = buf[i];
    }
    
}
#endif 

#ifdef UNIT_TEST
    #define main main_test
    int unitTestCnt = 5;
    bool testFlag = false;
    void setWorkingTrue(void)
    {
        working = true;
    }
    #define WAIT_FOR_BUSY_TEST   ((unitTestCnt-- == 0) ? (working = testFlag, false) : true)
#else
    #define WAIT_FOR_BUSY_TEST   (true) 
#endif
/**
 * @brief main
 * @return
 */
int main(int, char **)
{
    /*  Creating instances of Class  */
    /*  */
    std::shared_ptr<Gnss::GnssService> gnss_service = std::make_shared<Gnss::GnssService>();  
    std::shared_ptr<Gnss::GnssDBus> _GnssDBus ;   
    
    setlogmask (LOG_UPTO (LOG_INFO));

    openlog ("idneo_gnssService", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0); 
    syslog (LOG_NOTICE, "Gnss program started by User %d", getuid ());
    std::time_t _start_time = getTime();
    std::time_t _current_time = getTime();
    #if (LOG_ENABLE_TEST == 1)
    char       buf[80];
    currentDateTime(buf, true);
    debugOut<<"Opening and creating Logging files."<<std::endl;
    debugOut<<buf<<std::endl;
    freopen( buf, "w", stdout );
    currentDateTime(buf, false);
    freopen( buf, "w", stderr );
    debugOut<<"Logging for DR Test under these conditions:"<<std::endl;
    debugOut<<"Yaw = 0; Pitch = 0; Roll = 0"<<std::endl;
    #endif

    std::shared_ptr<Gnss::GnssUdp> _gnss_udp = std::make_shared<Gnss::GnssUdp>();
    std::shared_ptr<Gnss::GnssParseNmea> gnss_nemaFrames = std::make_shared<Gnss::GnssParseNmea>();
    int ret = gnss_service->createSocket(_gnss_udp, gnss_nemaFrames);
  
    
    const char* destinationName = "com.idneo.ublox";
    const char* objectPath = "/com/idneo/ublox";
    _GnssDBus = std::make_shared<Gnss::GnssDBus>(destinationName,objectPath); 

     
    debugOut<<"Gnss starting."<<std::endl;

    signal(SIGINT, gnss_signal_handler);
    signal(SIGKILL, gnss_signal_handler);
    
    if(0U == ret)
    {
         int error_reading_ublox = 1;
        std::string version; 
        while((working) && (error_reading_ublox))
        {
            try
            {   
                error_reading_ublox = 0;
                version = _GnssDBus->getVersion();
                debugOut<< version <<std::endl;
            }
            catch(  sdbus::Error& e)
            {
                error_reading_ublox = 1; 
                _GnssDBus->unregisterProxy();
                _GnssDBus->registerProxy();
                _GnssDBus = std::make_shared<Gnss::GnssDBus>(destinationName,objectPath); 
            }
            usleep(1000000);
        }

        _GnssDBus->registerDBusListener(gnss_service);
        debugOut<<"Gnss started."<<std::endl;
    
        while ((working) && (WAIT_FOR_BUSY_TEST))
        {    
            usleep(100000);
            
            _current_time = getTime();  
            if((_current_time - _start_time) >= TIME_SYSLOG_PUBLISH_S)
            {
                _start_time = getTime();
                /* Save data to syslog each 60s */ 
                gnss_nemaFrames->publishSyslogNmea();    
            }
            else
            {
                /* Misra mandatory else */
            }
        }  
        
        _GnssDBus->unRegisterDBusListener(gnss_service);
        ret |= gnss_service->closeSocket(); 
 
        closelog ();
        
        debugOut << "Gnss exiting." << std::endl;
        debugOut << "Gnss exited." << std::endl;
    }
    else
    {
        /*  Error opening some socket*/
        std::cerr<<"Error opening sockets."<<std::endl;
    }

    return ret;
}
