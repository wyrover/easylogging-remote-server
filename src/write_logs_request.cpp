#include "write_logs_request.h"
#include "request_type.h"

WriteLogsRequest::WriteLogsRequest(const std::string& jsonRequest) :
    m_jsonRequest(jsonRequest)
{
}

WriteLogsRequest::~WriteLogsRequest(void)
{
}

bool WriteLogsRequest::parseFromJson(const std::string& json)
{
    return true;
}

RequestType WriteLogsRequest::type(void) const
{
    return RequestType::WriteLogs;
}

bool WriteLogsRequest::valid(void) const
{
    return m_valid;
}

const char* WriteLogsRequest::lastError(void) const
{
    return m_lastError;
}

const std::string& WriteLogsRequest::jsonRequest(void) const
{
    return m_jsonRequest;
}
