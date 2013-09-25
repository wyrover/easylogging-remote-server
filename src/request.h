#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "request_type.h"

class Credentials;

class Request
{
public:
    explicit Request(const std::string& json);
    virtual ~Request(void);

    virtual bool parseFromJson(const std::string& json);
    virtual RequestType type(void) const = 0;

    bool valid(void) const;
    const char* lastError(void) const;
    const std::string& jsonRequest(void) const;
    void setError(const char* error);
    void makeValid(void);
    bool checkPermissions(Credentials* credentials) const;
private:
    std::string m_jsonRequest;
    const char* m_lastError;
    bool m_valid;
    std::string m_user;
    std::string m_password;
};

#endif // REQUEST_H
