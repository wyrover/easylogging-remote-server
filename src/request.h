#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "request_type.h"

class Request
{
public:
    Request(const std::string& jsonRequest);
protected:
    bool parseFromJson(const std::string& json);
    const RequestType& type(void) const { return m_type; }
private:
    std::string m_jsonRequest;
    RequestType m_type;
};

#endif // REQUEST_H
