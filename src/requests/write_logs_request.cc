#include "requests/write_logs_request.h"
#include "easylogging++.h"
#include "requests/request_type.h"
#include "json_packet.h"

WriteLogsRequest::WriteLogsRequest(JsonPacket* json, Credentials* credentials) :
    Request(json, credentials)
{
    buildFromJsonPacket(jsonPacket());
}

WriteLogsRequest::~WriteLogsRequest(void)
{
}

void WriteLogsRequest::buildFromJsonPacket(JsonPacket* jsonPacket)
{
    m_logger = jsonPacket->getString("logger", "remote");
    m_level = el::LevelHelper::castFromInt(static_cast<unsigned short>(jsonPacket->getInt("level", "0")));
    m_logMessage = jsonPacket->getString("log", "");
    m_vLevel = jsonPacket->getInt("vlevel", "0");
    m_func = jsonPacket->getString("func", "");
    m_file = jsonPacket->getString("file", "");
    m_line = jsonPacket->getInt("line", "0");
    if (valid() && m_level == el::Level::Unknown) {
        setLastError("Invalid severity level for log");
        setValid(false);
    }
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
