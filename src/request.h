#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "request_type.h"

class Request
{
public:
    Request(void) {}
    virtual ~Request(void) {}
    virtual bool parseFromJson(const std::string& json) = 0;
    virtual RequestType type(void) const = 0;
    virtual bool valid(void) const = 0;
    virtual const char* lastError(void) const = 0;
    virtual const std::string& jsonRequest(void) const;
};

#endif // REQUEST_H
