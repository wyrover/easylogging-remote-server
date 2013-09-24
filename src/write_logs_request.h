#ifndef WRITELOGSREQUEST_H
#define WRITELOGSREQUEST_H

#include "request.h"

class WriteLogsRequest : public Request
{
public:
    explicit WriteLogsRequest(const std::string& jsonRequest);
    virtual ~WriteLogsRequest(void);
    virtual bool parseFromJson(const std::string& json);
    virtual RequestType type(void) const;
    virtual bool valid(void) const;
    virtual const char* lastError(void) const;
    virtual const std::string &jsonRequest(void) const;
private:
    std::string m_jsonRequest;
    const char* m_lastError;
    bool m_valid;
};

#endif // WRITELOGSREQUEST_H
