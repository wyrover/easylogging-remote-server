#ifndef CONFIGURATION_UPDATE_REQUEST_H
#define CONFIGURATION_UPDATE_REQUEST_H

#include "requests/request.h"

class ConfigurationUpdateRequest : public Request
{
public:
    static std::vector<std::string> kRequiredKeys;

    ConfigurationUpdateRequest(JsonPacket* json, Credentials *credentials);
    virtual ~ConfigurationUpdateRequest(void);
    virtual inline RequestType type(void) const;
    virtual bool process(void);

    const std::string& logger(void) {
        return m_logger;
    }

    const std::string& configurationData(void) {
        return m_configurationData;
    }
private:
    std::string m_logger;
    std::string m_configurationData;
    virtual void buildFromJsonPacket(void);
};

#endif // CONFIGURATION_UPDATE_REQUEST_H
