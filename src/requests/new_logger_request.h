#ifndef NEW_LOGGER_REQUEST_H
#define NEW_LOGGER_REQUEST_H

#include <string>
#include "requests/request.h"

class NewLoggerRequest : public Request
{
public:
    NewLoggerRequest(JsonPacket *json);
    virtual ~NewLoggerRequest(void);
    virtual bool buildFromJsonPacket(JsonPacket* jsonPacket);
    virtual inline RequestType type(void) const;
    virtual bool process(void);
private:
    std::string m_logger;
};

#endif // NEW_LOGGER_REQUEST_H
