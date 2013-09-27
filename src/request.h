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
    virtual bool process(void) = 0;

    bool valid(void) const;
    void setValid(bool isValid);
    const std::string& lastError(void) const;
    void setLastError(const std::string& error);
    const std::string& jsonRequest(void) const;
    bool userHasPermissions(Credentials* credentials) const;
    const std::string& user(void) const;
private:
    std::string m_jsonRequest;
    std::string m_lastError;
    bool m_valid;
    std::string m_user;
    std::string m_password;
};

#endif // REQUEST_H
