#ifndef NEW_LOGGER_REQUEST_H
#define NEW_LOGGER_REQUEST_H

#include <string>
#include "requests/request.h"

class NewLoggerRequest : public Request
{
public:
    static std::vector<std::string> kRequiredKeys;

    NewLoggerRequest(JsonPacket* json, Credentials* credentials);
    virtual ~NewLoggerRequest(void);
    virtual inline RequestType type(void) const;
    virtual bool process(void);

    const std::string& logger(void) {
        return m_logger;
    }
private:
    std::string m_logger;
    virtual void buildFromJsonPacket(void);
};

#endif // NEW_LOGGER_REQUEST_H
