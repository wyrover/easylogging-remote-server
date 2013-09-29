#include "requests/configuration_update_request.h"
#include "json_packet.h"

const Request::Keys ConfigurationUpdateRequest::kRequiredKeys = Request::Keys {{
        "logger",
        "conf_data"
    }};

ConfigurationUpdateRequest::ConfigurationUpdateRequest(JsonPacket* json, Credentials* credentials) :
    Request(json, credentials, &kRequiredKeys)
{
    buildFromJsonPacket();
}

ConfigurationUpdateRequest::~ConfigurationUpdateRequest(void)
{
}

void ConfigurationUpdateRequest::buildFromJsonPacket(void)
{
    Request::buildFromJsonPacket();
    m_logger = jsonPacket()->getString("logger", "remote");
    m_configurationData = jsonPacket()->getString("conf_data", "");
    if (m_configurationData.empty()) {
        setValid(false);
        setLastError("Configuration data cannot be empty");
    }
}

RequestType ConfigurationUpdateRequest::type(void) const
{
    return RequestType::ConfigurationUpdate;
}

bool ConfigurationUpdateRequest::process(void)
{
    if (!Request::process()) {
        return false;
    }
    el::Logger* logger = el::Loggers::getLogger(m_logger, false);
    if (logger == nullptr) {
        LOG(ERROR) << "Logger [" << m_logger << "] not registered.";
        return false;
    }
    el::Configurations conf;
    conf.parseFromText(m_configurationData);
    VLOG(3) << "Reconfiguring logger [" << m_logger << "] with configurations [\n" << conf << "]";
    logger->configure(conf);
    return true;
}
