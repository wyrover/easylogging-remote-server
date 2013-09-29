#include "requests/flags_update_request.h"
#include "requests/request_factory.h"

const JsonPacket::Keys FlagsUpdateRequest::kRequiredKeys = JsonPacket::Keys {{
        Request::kKeyLoggingFlag,
        Request::kKeyLoggingFlagOperation
    }};

FlagsUpdateRequest::FlagsUpdateRequest(JsonPacket *json, Credentials *credentials) :
    Request(json, credentials, &kRequiredKeys)
{
    buildFromJsonPacket();
}


FlagsUpdateRequest::~FlagsUpdateRequest(void)
{
}

bool FlagsUpdateRequest::buildFromJsonPacket(void)
{
    if (!Request::buildFromJsonPacket()) {
        return false;
    }
    int loggingFlag;
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLoggingFlag, 0, &loggingFlag);
    if (valid() && loggingFlag == 0) {
        setLastError("Invalid logging flag");
        setValid(false);
        return false;
    }
    m_loggingFlag = static_cast<el::LoggingFlag>(loggingFlag);
    int operation;
    RequestFactory::updateTarget(jsonPacket(), Request::kKeyLoggingFlagOperation, 0, &operation);
    m_operation = static_cast<Operation>(operation);
    if (valid() && m_operation == Operation::Unknown) {
        setLastError("Invalid operation");
        setValid(false);
        return false;
    }
    return valid();
}

RequestType FlagsUpdateRequest::type(void) const
{
    return RequestType::FlagsUpdate;
}

bool FlagsUpdateRequest::process(void)
{
    if (!Request::process()) {
        return false;
    }
    if (m_operation == Operation::Add) {
        el::Helpers::addFlag(m_loggingFlag);
    } else if (m_operation == Operation::Remove) {
        el::Helpers::removeFlag(m_loggingFlag);
    }
    return true;
}
