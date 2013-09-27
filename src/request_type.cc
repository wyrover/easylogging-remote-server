#include "request_type.h"
#include <cstring>
#include "easylogging++.h"
#include "json_packet.h"

const char* RequestTypeHelper::convertToString(const RequestType& requestType)
{
    // Intel C++ does not yet support switch over strongly-typed enums so we use if-statements
    if (requestType == RequestType::WriteLogs)
        return "WRITE_LOGS";
    if (requestType == RequestType::NewLogger)
        return "NEW_LOGGER";
    if (requestType == RequestType::ConfigurationUpdate)
        return "CONFIGURATION_UPDATE";
    if (requestType == RequestType::RunCommand)
        return "RUN_COMMAND";
    return "UNKNOWN";
}

RequestType RequestTypeHelper::convertFromString(const char* requestTypeStr)
{
    if ((strcmp(requestTypeStr, "WRITE_LOGS") == 0) || (strcmp(requestTypeStr, "write_logs") == 0)) {
        return RequestType::WriteLogs;
    }
    if ((strcmp(requestTypeStr, "NEW_LOGGER") == 0) || (strcmp(requestTypeStr, "new_logger") == 0)) {
        return RequestType::NewLogger;
    }
    if ((strcmp(requestTypeStr, "CONFIGURATION_UPDATE") == 0) || (strcmp(requestTypeStr, "configuration_update") == 0)) {
        return RequestType::ConfigurationUpdate;
    }
    if ((strcmp(requestTypeStr, "RUN_COMMAND") == 0) || (strcmp(requestTypeStr, "run_command") == 0)) {
        return RequestType::RunCommand;
    }
    return RequestType::Unknown;
}

unsigned short RequestTypeHelper::convertToShort(const RequestType& requestType)
{
    return static_cast<unsigned short>(requestType);
}

RequestType RequestTypeHelper::convertFromShort(unsigned short requestTypeShort)
{
    return static_cast<RequestType>(requestTypeShort);
}

RequestType RequestTypeHelper::findRequestTypeFromJson(JsonPacket* json)
{
    return static_cast<RequestType>(json->getInt("type", "0"));
}
