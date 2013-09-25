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
private:

};

#endif // WRITELOGSREQUEST_H
