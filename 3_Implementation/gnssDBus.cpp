/*
 * GnssDBus.cpp
 *
 *  Created on: Aug 6, 2021
 *      Author: f59gv00
 */

#include "gnssDBus.hpp"
#include <iostream>
#include <mutex>
#include <ostream>
#include <bits/stdc++.h>
#include <thread>
#include <utility>

#if (DEBUG_GNSS_DBUS == 1)
#define debugOut std::cout 
#else
#define debugOut 0U && std::cout 
#endif 
     
/**
 * @brief Construct a new Gnss:: Gnss D Bus:: Gnss D Bus object
 * 
 * @param destination 
 * @param object_path 
 */
Gnss::GnssDBus::GnssDBus(std::string destination, std::string object_path): 
    sdbus::ProxyInterfaces<com::idneo::ublox_proxy>(std::move(destination), std::move(object_path))
{
    registerProxy();
}

/**
 * @brief Destroy the Gnss:: Gnss D Bus:: Gnss D Bus object
 * 
 */
Gnss::GnssDBus::~GnssDBus()
{ 
    unregisterProxy();
}


bool Gnss::GnssDBus::registerDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener)
{
    bool retVal = false;
    debugOut<<__PRETTY_FUNCTION__<<" "<<std::this_thread::get_id()<<std::endl;
    std::lock_guard<std::mutex> guard(listener_mutex);
    if(listener.get() != nullptr)
    {
        dbus_listener_list.push_back(listener);
        retVal = true;
    }
    else
    {
        std::cerr<<"Error registering null pointer"<<std::endl;
    }

    return retVal;
}

/**
 * @brief Function to unregister a Listener
 * 
 * @param listener  Listener to unregister.
 * @return true     The listener has been unregistered correctly
 * @return false    The listener has not been unregistered
 */
bool Gnss::GnssDBus::unRegisterDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener)
{
    bool retVal = false;
    debugOut<<__PRETTY_FUNCTION__<<" "<<std::this_thread::get_id()<<std::endl;
    std::lock_guard<std::mutex> guard(listener_mutex);
    std::vector<std::shared_ptr<IDbusListener>>::iterator it;

    it = std::find( dbus_listener_list.begin(), 
                    dbus_listener_list.end(), 
                    listener);

    if (it != dbus_listener_list.end()) 
    {
        dbus_listener_list.erase(it);
        retVal = true;
    }
    else
    {
        /*  The listener has not been unregistered */
    }

    return retVal;
}
 
/**
 * @brief Function which rises once we have received an event which indicates
 *          that there is a new Ublox state
 * 
 * @param status String which contains the Status state.
 */
void Gnss::GnssDBus::onUbloxState(const std::string& status)
{  
    std::lock_guard<std::mutex> guard(listener_mutex);
    std::for_each(  dbus_listener_list.begin(),
                    dbus_listener_list.end(),
                    [&](std::shared_ptr<Gnss::IDbusListener>& l) 
    {
        l->onDbusUbloxState(status); 
    });
}

/**
 * @brief Function which rises once we have received an event which indicates
 *          that there is a new Nmea Frame
 * 
 * @param value String which contains the NMEA Frame
 */
void Gnss::GnssDBus::onNmeaNewFrames(const std::string& value)
{  
    debugOut << value  << std::endl; 

    std::lock_guard<std::mutex> guard(listener_mutex);
    std::for_each(  dbus_listener_list.begin(),
                    dbus_listener_list.end(),
                    [&](std::shared_ptr<Gnss::IDbusListener>& l) 
    {
        l->onDbusNmeaFrames(value); 
    });

}
