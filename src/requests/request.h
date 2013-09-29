#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "requests/request_type.h"
#include "easylogging++.h"
#include "json_packet.h"

class Credentials;

class Request : public el::Loggable
{
public:

    static const char* kKeyUser;
    static const char* kKeyPassword;
    static const char* kKeyType;
    static const char* kKeyLogger;
    static const char* kKeyConfigurationData;
    static const char* kKeyLogMessage;
    static const char* kKeyVerboseLevel;
    static const char* kKeyFunc;
    static const char* kKeyFile;
    static const char* kKeyLine;
    static const char* kKeyLevel;
    static const char* kKeyLoggingFlag;
    static const char* kKeyLoggingFlagOperation;

    virtual ~Request(void);
    virtual RequestType type(void) const = 0;

    virtual bool process(void);

    JsonPacket* jsonPacket(void) const { return m_jsonPacket; }

    const JsonPacket::Keys* requiredKeys(void) const { return m_requiredKeys; }
    void setRequiredKeys(const JsonPacket::Keys* keys) { m_requiredKeys = keys; }

    bool valid(void) const { return m_valid; }
    void setValid(bool isValid) { m_valid = isValid; }

    const std::string& lastError(void) const { return m_lastError; }
    void setLastError(const std::string& error) { m_lastError = error; }

    bool userHasPermissions(Credentials* credentials) const;

    const std::string& user(void) const { return m_user; }

    virtual void log(std::ostream&) const;
protected:
    Request(JsonPacket* jsonPacket, Credentials* credentials, const JsonPacket::Keys* requiredKeys);
    virtual bool buildFromJsonPacket(void);
private:
    JsonPacket* m_jsonPacket;
    Credentials* m_credentials;
    const JsonPacket::Keys* m_requiredKeys;
    std::string m_lastError;
    bool m_valid;
    std::string m_user;
    std::string m_password;
};

#endif // REQUEST_H
