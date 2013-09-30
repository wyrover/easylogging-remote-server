#ifndef JSON_PACKET_H
#define JSON_PACKET_H

#include <jsoncpp/json.h>
#include "easylogging++.h"

class JsonPacket : public el::Loggable
{
public:
    typedef std::vector<const char*> Keys;
    JsonPacket(std::string&& jsonRequest);

    bool valid(void) const { return m_valid; }
    void setValid(bool valid) { m_valid = valid; }

    const std::string& lastError(void) const { return m_lastError; }
    void setLastError(const std::string& lastError) { m_lastError = lastError; }

    int getInt(const std::string& key, int defaultValue) const;
    unsigned int getUInt(const std::string& key, unsigned int defaultValue) const;
    std::string getString(const std::string& key, const std::string& defaultValue) const;

    bool hasKey(const std::string& key) const;
    bool hasKeys(const Keys* keys) const;

    virtual void log(std::ostream &) const;
private:
    std::string m_jsonRequest;
    Json::Value m_root;
    bool m_valid;
    std::string m_lastError;
};

#endif // JSON_PACKET_H
