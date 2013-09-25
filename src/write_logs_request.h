#ifndef WRITELOGSREQUEST_H
#define WRITELOGSREQUEST_H

#include "request.h"

class WriteLogsRequest : public Request
{
public:
    explicit WriteLogsRequest(const std::string& jsonRequest);
    virtual ~WriteLogsRequest(void);

    virtual bool parseFromJson(const std::string& json);
    virtual inline RequestType type(void) const;
    virtual bool process(void);
private:

};

#endif // WRITELOGSREQUEST_H
