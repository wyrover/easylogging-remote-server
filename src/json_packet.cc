
#include "json_packet.h"
#include "easylogging++.h"

JsonPacket::JsonPacket(const std::string& jsonRequest)
{
    Json::Reader reader;
    try {
        if (!reader.parse(jsonRequest, m_root)) {
            m_valid = false;
            m_lastError = "Invalid json: " + jsonRequest;
        }
    } catch (...) {
        m_valid = false;
        m_lastError = "Invalid json: " + jsonRequest;
    }
    m_valid = true;
    m_lastError = "";
}


int JsonPacket::getInt(const std::string& key, const Json::Value& defaultValue) const
{
    Json::Value json = m_root.get(key, defaultValue);
    if (!json.isInt()) {
        return defaultValue.asInt();
    }
    return json.asInt();
}

std::string JsonPacket::getString(const std::string& key, const Json::Value& defaultValue) const
{
    Json::Value json = m_root.get(key, defaultValue);
    return json.asString();
}
