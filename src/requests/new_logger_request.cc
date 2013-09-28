#include "requests/new_logger_request.h"
#include "json_packet.h"

NewLoggerRequest::NewLoggerRequest(JsonPacket* json, Credentials* credentials) :
    Request(json, credentials)
{
    buildFromJsonPacket(jsonPacket());
}

NewLoggerRequest::~NewLoggerRequest(void)
{
}

void NewLoggerRequest::buildFromJsonPacket(JsonPacket* jsonPacket)
{
    m_logger = jsonPacket->getString("logger", "remote");
    if (!el::Logger::isValidId(m_logger)) {
        setLastError("Invalid logger ID [" + m_logger + "] to register.");
        setValid(false);
    }
}

RequestType NewLoggerRequest::type(void) const
{
    return RequestType::NewLogger;
}

bool NewLoggerRequest::process(void)
{
    if (!Request::process()) {
        return false;
    }
    if (el::Loggers::getLogger(m_logger, true) == nullptr) {
        LOG(ERROR) << "Unable to register [" << m_logger << "], unknown internal error.";
        return false;
    }
    return true;
}
