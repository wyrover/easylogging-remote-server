#include "requests/request.h"
#include "easylogging++.h"
#include "requests/request_type.h"
#include "credentials.h"
#include "json_packet.h"

Request::Request(JsonPacket* json, Credentials* credentials, const Keys *requiredKeys) :
    m_jsonPacket(json), m_credentials(credentials)
{
    setRequiredKeys(requiredKeys);
    setLastError("");
    setValid(true);
}

Request::~Request(void)
{
}

void Request::buildFromJsonPacket(void)
{
    m_user = m_jsonPacket->getString("user", "");
    m_password = m_jsonPacket->getString("pwd", "");
    LOG_IF(!m_user.empty(), INFO) << "Request received by [" << m_user << "]";
    if (m_credentials->requireCredentials() && (m_user.empty() || m_password.empty())) {
        setLastError("Server requires credentials to process the request. "
                     "Please verify username and password is provided in json request.");
        setValid(false);
    }
    if (valid() && !m_jsonPacket->hasKeys(requiredKeys())) {
        setLastError("Request [" + el::Helpers::convertTemplateToStdString(*this) + "] needs at least following keys: " + el::Helpers::convertTemplateToStdString(*requiredKeys()));
        setValid(false);
        return;
    }
}

bool Request::userHasPermissions(Credentials* credentials) const
{
    return credentials->check(m_user, m_password, PermissionsHelper::convertRequestTypeShortToPermissions(RequestTypeHelper::convertToShort(type())));
}

bool Request::process(void) {
    if (!valid()) {
        LOG(WARNING) << "Not processing [" << *this << "], invalid request; last error: " << m_lastError;
        return false;
    } else {
        LOG(INFO) << "Processing request [" << *this << "]";
    }
    return true;
}

void Request::log(std::ostream& os) const
{
    os << RequestTypeHelper::convertToString(type());
}
