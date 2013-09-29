#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "requests/request_type.h"
#include "easylogging++.h"

class Credentials;
class JsonPacket;

class Request : public el::Loggable
{
public:
    typedef std::vector<std::string> Keys;
    virtual ~Request(void);
    virtual RequestType type(void) const = 0;

    virtual bool process(void);

    JsonPacket* jsonPacket(void) const { return m_jsonPacket; }

    const Keys* requiredKeys(void) const { return m_requiredKeys; }
    void setRequiredKeys(const Keys* keys) { m_requiredKeys = keys; }

    bool valid(void) const { return m_valid; }
    void setValid(bool isValid) { m_valid = isValid; }

    const std::string& lastError(void) const { return m_lastError; }
    void setLastError(const std::string& error) { m_lastError = error; }

    bool userHasPermissions(Credentials* credentials) const;

    const std::string& user(void) const { return m_user; }

    virtual void log(std::ostream&) const;
protected:
    Request(JsonPacket* jsonPacket, Credentials* credentials, const Keys* requiredKeys);
    virtual void buildFromJsonPacket(void);
private:
    JsonPacket* m_jsonPacket;
    Credentials* m_credentials;
    const Keys* m_requiredKeys;
    std::string m_lastError;
    bool m_valid;
    std::string m_user;
    std::string m_password;
};

#endif // REQUEST_H
