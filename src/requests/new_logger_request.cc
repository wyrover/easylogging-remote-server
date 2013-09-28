#include "requests/new_logger_request.h"
#include "json_packet.h"

NewLoggerRequest::NewLoggerRequest(JsonPacket* json) :
    Request(json)
{
    buildFromJsonPacket(jsonPacket());
}

NewLoggerRequest::~NewLoggerRequest(void)
{
}

bool NewLoggerRequest::buildFromJsonPacket(JsonPacket* jsonPacket)
{
    m_logger = jsonPacket->getString("logger", "remote");
    setValid(true);
    return true;
}

RequestType NewLoggerRequest::type(void) const
{
    return RequestType::NewLogger;
}

bool NewLoggerRequest::process(void)
{
    VLOG(3) << "Processing request [" << *this << "]";
    return true;
}
