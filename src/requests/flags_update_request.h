#ifndef FLAGS_UPDATE_REQUEST_H
#define FLAGS_UPDATE_REQUEST_H

#include "requests/request.h"

class FlagsUpdateRequest : public Request
{
public:
    static const JsonPacket::Keys kRequiredKeys;

    enum class Operation {
        Unknown = 0,
        Add = 1,
        Remove = 2
    };

    FlagsUpdateRequest(JsonPacket* json, Credentials* credentials);
    virtual ~FlagsUpdateRequest(void);

    virtual inline RequestType type(void) const;
    virtual bool process(void);
protected:
    el::LoggingFlag m_loggingFlag;
    Operation m_operation;

    virtual bool buildFromJsonPacket(void);
};

#endif // FLAGS_UPDATE_REQUEST_H
