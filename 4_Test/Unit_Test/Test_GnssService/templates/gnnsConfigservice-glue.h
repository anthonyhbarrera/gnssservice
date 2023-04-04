
/*
 * This file !
 */

#ifndef __sdbuscpp___home_idneo_projects_CANOO_software_GNSS_gnssservice_build_gnnsConfigservice_glue_h__proxy__H__
#define __sdbuscpp___home_idneo_projects_CANOO_software_GNSS_gnssservice_build_gnnsConfigservice_glue_h__proxy__H__

#include <string>
#include <errno.h>

namespace sdbus{
    
class Error  : public std::runtime_error
{
    public:
    Error(const std::string& name, const std::string& message) 
        : std::runtime_error("[" + name + "] " + message)
        , name_(name)
        , message_(message)
    {
    }

    const std::string& getName() const
    {
        return name_;
    }

    const std::string& getMessage() const
    {
        return message_;
    }

    bool isValid() const
    {
        return !getName().empty();
    }

private:
    std::string name_;
    std::string message_;
};
template <class T>
class ProxyInterfaces {
    
    public:
    ProxyInterfaces(std::string destination, std::string objectPath)
    {

    }

    void registerProxy()
    {

    }

    void unregisterProxy()
    {

    } 

    std::string getVersion()
    {
        std::string result = ""; 
        return result;
    }
    
};
}
 

namespace com {
namespace idneo {

class ublox_proxy
{   

};

}} // namespaces

 
#endif
