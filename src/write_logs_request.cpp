#include "write_logs_request.h"
#include <jsoncpp/json.h>
#include "easylogging++.h"
#include "request_type.h"

WriteLogsRequest::WriteLogsRequest(const std::string& json) :
    Request(json)
{
    parseFromJson(jsonRequest());
}

WriteLogsRequest::~WriteLogsRequest(void)
{
}

bool WriteLogsRequest::parseFromJson(const std::string& json)
{
    Json::Value root;
    Json::Reader reader;
    try {
        if (!reader.parse(json, root)) {
            LOG(ERROR) << "Invalid json request: " << json;
            return false;
        }
    } catch (...) {
        return false;
    }
    // Logger
    Json::Value jsonLogger = root.get("logger", "remote");
    m_logger = jsonLogger.asString();
    // Level
    Json::Value jsonLevel = root.get("level", "0");
    if (jsonLevel.isInt()) {
        m_level = el::LevelHelper::castFromInt(static_cast<unsigned short>(jsonLevel.asUInt()));
    }
    // Log
    Json::Value jsonLog = root.get("log", "");
    m_logMessage = jsonLog.asString();
    // Verbose Level
    if (m_level == el::Level::Verbose) {
        Json::Value jsonVLevel = root.get("vlevel", "0");
        m_vLevel = jsonVLevel.asInt();
    }
    // Func
    Json::Value jsonFunc = root.get("func", "");
    m_func = jsonFunc.asString();
    // File
    Json::Value jsonFile = root.get("file", "");
    m_file = jsonFile.asString();
    // Line
    Json::Value jsonLine = root.get("line", "0");
    if (jsonLine.isUInt()) {
        m_line = static_cast<unsigned int>(jsonLine.asUInt());
    }
    markValid();
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
