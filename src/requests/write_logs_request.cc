#include "requests/write_logs_request.h"
#include "easylogging++.h"
#include "requests/request_type.h"
#include "requests/request_factory.h"
#include "json_packet.h"

const JsonPacket::Keys WriteLogsRequest::kRequiredKeys = JsonPacket::Keys {{
        Request::kKeyLevel,
        Request::kKeyLogMessage
    }};

WriteLogsRequest::WriteLogsRequest(JsonPacket* json, Credentials* credentials) :
    Request(json, credentials, &kRequiredKeys)
{
    buildFromJsonPacket();
}

WriteLogsRequest::~WriteLogsRequest(void)
{
}

bool WriteLogsRequest::buildFromJsonPacket(void)
{
    if (!Request::buildFromJsonPacket()) {
        return false;
    }
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLogger, "remote", &m_logger);

    int levelInt;
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLevel, 0, &levelInt);
    m_level = el::LevelHelper::castFromInt(static_cast<unsigned short>(levelInt));
    if (valid() && m_level == el::Level::Unknown) {
        setLastError("Invalid severity level for log");
        setValid(false);
        return false;
    }

    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLogMessage, "", &m_logMessage, true);
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyVerboseLevel, 0, &m_vLevel, true);
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyFunc, "", &m_func, true);
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyFile, "", &m_file, true);
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLine, 0, &m_line, true);
    return valid();
}

RequestType WriteLogsRequest::type(void) const
{
    return RequestType::WriteLogs;
}

bool WriteLogsRequest::process(void)
{
    if (!Request::process()) {
        return false;
    }
    if (m_level == el::Level::Verbose && !VLOG_IS_ON(m_vLevel)) {
        LOG(WARNING) << "Verbose log level [" << m_vLevel << "] is not enabled, ignoring...";
        return false;
    } else {
        el::base::Writer(m_logger, m_level, m_file.c_str(), m_line, m_func.c_str(), m_vLevel) << m_logMessage;
    }
    return true;
}
