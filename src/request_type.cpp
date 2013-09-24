#include "request_type.h"
#include <cstring>

const char* RequestTypeHelper::convertToString(const RequestType& requestType)
{
    switch (requestType) {
        case RequestType::WriteLogs:
            return "WRITE_LOGS";
            break;
        case RequestType::NewLogger:
            return "NEW_LOGGER";
            break;
        case RequestType::ConfigurationUpdate:
            return "CONFIGURATION_UPDATE";
            break;
        default:
            return "UNKNOWN";
    }
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
    return RequestType::Unknown;
}
