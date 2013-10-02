#include "json_packet.h"

JsonPacket::JsonPacket(std::string&& jsonRequest) :
    m_jsonRequest(std::move(jsonRequest))
{
    Json::Reader reader;
    try {
        if (!reader.parse(m_jsonRequest, m_root)) {
            setValid(false);
            setLastError("Invalid JSON: " + m_jsonRequest);
        } else {
            setValid(true);
            setLastError("");
        }
    } catch (...) {
        setValid(false);
        setLastError("Invalid JSON: " + m_jsonRequest);
    }
}


int JsonPacket::getInt(const std::string& key, int defaultValue) const
{
    if (!hasKey(key)) {
        return defaultValue;
    }
    Json::Value json = m_root.get(key, Json::Value(defaultValue));
    if (!json.isConvertibleTo(Json::intValue)) {
        return defaultValue;
    }
    return json.asInt();
}

std::string JsonPacket::getString(const std::string& key, const std::string& defaultValue) const
{
    if (!hasKey(key)) {
        return defaultValue;
    }
    return m_root.get(key, Json::Value(defaultValue)).asString();
}

bool JsonPacket::hasKey(const std::string& key) const
{
    return m_root.isMember(key);
}

bool JsonPacket::hasKeys(const JsonPacket::Keys* keys) const
{
    for (auto&& key : *keys) {
        if (!m_root.isMember(key)) {
            return false;
        }
    }
    return true;
}

void JsonPacket::log(std::ostream& os) const
{
    os << m_jsonRequest;
}
