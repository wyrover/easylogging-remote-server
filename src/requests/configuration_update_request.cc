#include "requests/configuration_update_request.h"
#include "requests/request_factory.h"
#include "json_packet.h"

const JsonPacket::Keys ConfigurationUpdateRequest::kRequiredKeys = JsonPacket::Keys {{
        Request::kKeyLogger,
        Request::kKeyConfigurationData
    }};

ConfigurationUpdateRequest::ConfigurationUpdateRequest(JsonPacket* json, Credentials* credentials) :
    Request(json, credentials, &kRequiredKeys)
{
    buildFromJsonPacket();
}

ConfigurationUpdateRequest::~ConfigurationUpdateRequest(void)
{
}

bool ConfigurationUpdateRequest::buildFromJsonPacket(void)
{
    if (!Request::buildFromJsonPacket()) {
        return false;
    }
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLogger, "remote", &m_logger);
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyConfigurationData, "", &m_configurationData);

    if (m_configurationData.empty()) {
        setValid(false);
        setLastError("Configuration data cannot be empty");
        return false;
    }
    return valid();
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
        setLastError("Logger [" + m_logger + "] not registered.");
        setValid(false);
        return false;
    }
    if (m_configurationData.empty()) {
        setLastError("Configuration data empty.");
        setValid(false);
        return false;
    }
    el::Configurations conf;
    conf.parseFromText(m_configurationData);
    VLOG(3) << "Reconfiguring logger [" << m_logger << "] with configurations [\n" << conf << "]";
    logger->configure(conf);
    return true;
}
