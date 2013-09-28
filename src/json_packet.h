#ifndef JSON_PACKET_H
#define JSON_PACKET_H

#include <jsoncpp/json.h>

class JsonPacket
{
public:
    JsonPacket(const std::string& jsonRequest);

    bool valid(void) const { return m_valid; }
    void setValid(bool valid) { m_valid = valid; }

    const std::string& lastError(void) const { return m_lastError; }
    void setLastError(const std::string& lastError) { m_lastError = lastError; }

    int getInt(const std::string& key, const Json::Value& defaultValue) const;
    std::string getString(const std::string& key, const Json::Value& defaultValue) const;
private:
    Json::Value m_root;
    bool m_valid;
    std::string m_lastError;
};

#endif // JSON_PACKET_H
