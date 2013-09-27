#include "write_logs_request.h"
#include "easylogging++.h"
#include "json_packet.h"
#include "request_type.h"

WriteLogsRequest::WriteLogsRequest(JsonPacket* json) :
    Request(json)
{
    parseFromJson(jsonPacket());
}

WriteLogsRequest::~WriteLogsRequest(void)
{
}

bool WriteLogsRequest::parseFromJson(JsonPacket* jsonPacket)
{
    m_logger = jsonPacket->getString("logger", "remote");
    m_level = el::LevelHelper::castFromInt(static_cast<unsigned short>(jsonPacket->getInt("level", "0")));
    m_logMessage = jsonPacket->getString("log", "");
    m_vLevel = jsonPacket->getInt("vlevel", "0");
    m_func = jsonPacket->getString("func", "");
    m_file = jsonPacket->getString("file", "");
    m_line = jsonPacket->getInt("line", "0");
    setValid(true);
    return true;
}

RequestType WriteLogsRequest::type(void) const
{
    return RequestType::WriteLogs;
}

bool WriteLogsRequest::process(void)
{
    VLOG(3) << "Processing request [" << RequestTypeHelper::convertToString(type()) << "]";
    if (m_level == el::Level::Verbose && !VLOG_IS_ON(m_vLevel)) {
        VLOG(1) << "Verbose log level [" << m_vLevel << "] is not enabled, ignoring...";
        return false;
    } else {
        el::base::Writer(m_logger, m_level, m_file.c_str(), m_line, m_func.c_str(), m_vLevel) << m_logMessage;
    }
    return true;
}

const std::string& WriteLogsRequest::logger(void) {
    return m_logger;
}

const el::Level& WriteLogsRequest::level(void) {
    return m_level;
}

const std::string& WriteLogsRequest::func(void) {
    return m_func;
}

const std::string& WriteLogsRequest::file(void) {
    return m_file;
}

unsigned long int WriteLogsRequest::line(void) const {
    return m_line;
}

int WriteLogsRequest::vLevel(void) const {
    return m_vLevel;
}

const std::string& WriteLogsRequest::logMessage(void) {
    return m_logMessage;
}
