/*
 * ModemDBus.hpp
 *
 *  Created on: Aug 6, 2021
 *      Author: f59gv00
 */

#ifndef _GNSSDBUS_HPP_
#define _GNSSDBUS_HPP_
 
 
#include <mutex>
#include <memory>
#include <vector>
#include <string>
#include "gnnsConfigservice-glue.h" 

#define DEBUG_GNSS_DBUS  0

namespace Gnss {

class IDbusListener
{
public: 
    virtual void onDbusNmeaFrames(const std::string& value) = 0;
    virtual void onDbusUbloxState(const std::string& value) = 0;
};

class GnssDBus: 
    public sdbus::ProxyInterfaces<com::idneo::ublox_proxy>
{
public:
    GnssDBus(std::string destination, std::string object_path);
    ~GnssDBus();
    bool registerDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener);
    bool unRegisterDBusListener(const std::shared_ptr<Gnss::IDbusListener>& listener);
private:
    std::mutex listener_mutex;
    std::vector<std::shared_ptr<Gnss::IDbusListener>> dbus_listener_list;

#ifdef UNIT_TEST
    public:
#endif
    void onUbloxState(const std::string& status);
    void onNmeaNewFrames(const std::string& value);
}; 
}
#endif /* _MODEMDBUS_HPP_ */
