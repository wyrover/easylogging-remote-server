#include "request_type.h"
#include <cstring>
#include <jsoncpp/json.h>
#include "easylogging++.h"

const char* RequestTypeHelper::convertToString(const RequestType& requestType)
{
    switch (requestType) {
        case RequestType::WriteLogs:
            return "WRITE_LOGS";
        case RequestType::NewLogger:
            return "NEW_LOGGER";
        case RequestType::ConfigurationUpdate:
            return "CONFIGURATION_UPDATE";
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

unsigned short RequestTypeHelper::convertToShort(const RequestType& requestType)
{
    return static_cast<RequestType>(requestType);
}

RequestType RequestTypeHelper::convertFromShort(unsigned short requestTypeShort)
{
    return static_cast<RequestType>(requestTypeShort);
}

RequestType RequestTypeHelper::findRequestTypeFromJson(const std::string& json)
{
    Json::Value root;
    Json::Reader reader;
    try {
        if (!reader.parse(json, root)) {
            LOG(ERROR) << "Invalid json request: " << json;
            return RequestType::Unknown;
        }
        Json::Value jsonType = root.get("type", "0");
        return static_cast<RequestType>(static_cast<unsigned short>(jsonType.asUInt()));
    } catch (...) {
        LOG(ERROR) << "Request type not specified: " << json;
        return RequestType::Unknown;
    }
}
