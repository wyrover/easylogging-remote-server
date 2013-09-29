#include "requests/request.h"
#include "easylogging++.h"
#include "requests/request_type.h"
#include "requests/request_factory.h"
#include "credentials.h"

const char* Request::kKeyUser = "user";
const char* Request::kKeyPassword = "pwd";
const char* Request::kKeyType = "type";
const char* Request::kKeyLogger = "logger";
const char* Request::kKeyConfigurationData = "conf_data";
const char* Request::kKeyLogMessage = "log";
const char* Request::kKeyVerboseLevel = "vlevel";
const char* Request::kKeyFunc = "func";
const char* Request::kKeyFile = "file";
const char* Request::kKeyLine = "line";
const char* Request::kKeyLevel = "level";
const char* Request::kKeyLoggingFlag = "flag";
const char* Request::kKeyLoggingFlagOperation = "oper";

Request::Request(JsonPacket* json, Credentials* credentials, const JsonPacket::Keys* requiredKeys) :
    m_jsonPacket(json), m_credentials(credentials)
{
    setRequiredKeys(requiredKeys);
    setLastError("");
    setValid(true);
}

Request::~Request(void)
{
}

bool Request::buildFromJsonPacket(void)
{
    RequestFactory::updateTarget(m_jsonPacket, kKeyUser, "", &m_user, false);
    RequestFactory::updateTarget(m_jsonPacket, kKeyPassword, "", &m_password, false);

    LOG_IF(!m_user.empty(), INFO) << "Request received by [" << m_user << "]";
    if (m_credentials->requireCredentials() && (m_user.empty() || m_password.empty())) {
        setLastError("Server requires credentials to process the request. "
                     "Please verify username and password is provided in json request.");
        setValid(false);
        return false;
    } else if (!m_jsonPacket->hasKeys(requiredKeys())) {
        setLastError("Request [" + el::Helpers::convertTemplateToStdString(*this) + "] needs at least following keys: " + el::Helpers::convertTemplateToStdString(*requiredKeys()));
        setValid(false);
        return false;
    }
    return valid();
}

bool Request::userHasPermissions(Credentials* credentials) const
{
    return credentials->check(m_user, m_password, PermissionsHelper::convertRequestTypeShortToPermissions(RequestTypeHelper::convertToShort(type())));
}

bool Request::process(void) {
    if (valid()) {
        LOG(INFO) << "Processing request [" << *this << "]";
    } else {
        LOG(WARNING) << "Not processing [" << *this << "], invalid request; last error: " << m_lastError;
        return false;
    }
    return true;
}

void Request::log(std::ostream& os) const
{
    os << RequestTypeHelper::convertToString(type());
}
