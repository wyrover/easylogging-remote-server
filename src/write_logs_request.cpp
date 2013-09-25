#include "write_logs_request.h"
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
    makeValid();
    return true;
}

RequestType WriteLogsRequest::type(void) const
{
    return RequestType::WriteLogs;
}

bool WriteLogsRequest::process(void)
{
    VLOG(3) << "Processing request [" << RequestTypeHelper::convertToString(type()) << "]";

    return true;
}
