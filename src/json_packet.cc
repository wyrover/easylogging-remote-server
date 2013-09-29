
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
    if (!hasKey(key)) {
        return -1;
    }
    Json::Value json = m_root.get(key, defaultValue);
    if (!json.isConvertibleTo(Json::intValue)) {
        return defaultValue.asInt();
    }
    return json.asInt();
}

std::string JsonPacket::getString(const std::string& key, const Json::Value& defaultValue) const
{
    if (!hasKey(key)) {
        return std::string("!invalid");
    }
    return m_root.get(key, defaultValue).asString();
}

bool JsonPacket::hasKey(const std::string& key) const
{
    return m_root.isMember(key);
}

bool JsonPacket::hasKeys(std::vector<std::string>* keys) const
{
    for (auto&& key : *keys) {
        if (!m_root.isMember(key)) {
            return false;
        }
    }
    return true;
}
