#ifndef NEW_LOGGER_REQUEST_H
#define NEW_LOGGER_REQUEST_H

#include "requests/request.h"

class NewLoggerRequest : public Request
{
public:
    static const JsonPacket::Keys kRequiredKeys;

    static const char* kKeyLogger;

    NewLoggerRequest(JsonPacket* json, Credentials* credentials);
    virtual ~NewLoggerRequest(void);
    virtual inline RequestType type(void) const;
    virtual bool process(void);

    const std::string& logger(void) {
        return m_logger;
    }
private:
    std::string m_logger;
    virtual bool buildFromJsonPacket(void);
};

#endif // NEW_LOGGER_REQUEST_H
