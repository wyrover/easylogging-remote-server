#include "requests/new_logger_request.h"
#include "requests/request_factory.h"
#include "json_packet.h"

const JsonPacket::Keys NewLoggerRequest::kRequiredKeys = JsonPacket::Keys {{
        Request::kKeyLogger
    }};

NewLoggerRequest::NewLoggerRequest(JsonPacket* json, Credentials* credentials) :
    Request(json, credentials, &kRequiredKeys)
{
    buildFromJsonPacket();
}

NewLoggerRequest::~NewLoggerRequest(void)
{
}

bool NewLoggerRequest::buildFromJsonPacket(void)
{
    if (!Request::buildFromJsonPacket()) {
        return false;
    }
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLogger, "remote", &m_logger);

    if (!el::Logger::isValidId(m_logger)) {
        setLastError("Invalid logger ID [" + m_logger + "] to register.");
        setValid(false);
        return false;
    }
    return valid();
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
        setLastError("Unable to register [" + m_logger + "], unknown internal error.");
        setValid(false);
        return false;
    }
    return true;
}
