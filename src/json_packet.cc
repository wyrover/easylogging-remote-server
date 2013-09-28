
#include "json_packet.h"

JsonPacket::JsonPacket(const std::string& jsonRequest)
{
    Json::Reader reader;
    try {
        if (!reader.parse(jsonRequest, m_root)) {
            setValid(false);
            setLastError("Invalid json: " + jsonRequest);
        } else {
            setValid(true);
            setLastError("");
        }
    } catch (...) {
        setValid(false);
        setLastError("Invalid json: " + jsonRequest);
    }
}


int JsonPacket::getInt(const std::string& key, const Json::Value& defaultValue) const
{
    if (!m_root.isMember(key)) {
        return defaultValue.asInt();
    }
    Json::Value json = m_root.get(key, defaultValue);
    if (!json.isConvertibleTo(Json::intValue)) {
        return defaultValue.asInt();
    }
    return json.asInt();
}

std::string JsonPacket::getString(const std::string& key, const Json::Value& defaultValue) const
{
    Json::Value json = m_root.get(key, defaultValue);
    return json.asString();
}
