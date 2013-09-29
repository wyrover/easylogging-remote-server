#include "requests/request_factory.h"
#include "requests/request.h"
#include "requests/write_logs_request.h"
#include "requests/new_logger_request.h"
#include "requests/configuration_update_request.h"

Request* RequestFactory::buildRequest(JsonPacket* jsonPacket, Credentials* credentials)
{
    Request* request = nullptr;

    if (!jsonPacket->hasKey("type")) {
        LOG(ERROR) << "Request type not received";
    } else {
        RequestType type = RequestTypeHelper::findRequestTypeFromJson(jsonPacket);
        // Intel C++ does not yet support switch over strongly-typed enums so we use if-statements
        if (type == RequestType::WriteLogs) {
            request = new WriteLogsRequest(jsonPacket, credentials);
        } else if (type == RequestType::NewLogger) {
            request = new NewLoggerRequest(jsonPacket, credentials);
        } else if (type == RequestType::ConfigurationUpdate) {
            request = new ConfigurationUpdateRequest(jsonPacket, credentials);
        } else {
            LOG(ERROR) << "Invalid request type received";
        }
    }
    return request;
}
