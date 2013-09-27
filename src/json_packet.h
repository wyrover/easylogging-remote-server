#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <jsoncpp/json.h>

class JsonPacket
{
public:
    JsonPacket(const std::string& jsonRequest);
    bool valid(void) const { return m_valid; }
    const std::string& lastError(void) const { return m_lastError; }

    int getInt(const std::string& key, const Json::Value& defaultValue) const;
    std::string getString(const std::string& key, const Json::Value& defaultValue) const;
private:
    Json::Value m_root;
    bool m_valid;
    std::string m_lastError;
};

#endif // JSON_UTILS_H
