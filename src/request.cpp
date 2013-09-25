#include "request.h"
#include <jsoncpp/json.h>
#include "easylogging++.h"
#include "credentials.h"
#include "request_type.h"

static Permissions convertRequestTypeToPermissions(const RequestType& requestType) {
    switch (requestType) {
        case RequestType::WriteLogs:
            return Permissions::WriteLogs;
        case RequestType::NewLogger:
            return Permissions::NewLogger;
        case RequestType::ConfigurationUpdate:
            return Permissions::ConfigurationUpdate;
        default:
            return Permissions::Unknown;
    }
}

Request::Request(const std::string& json) :
    m_jsonRequest(json)
{
    parseFromJson(jsonRequest());
}

Request::~Request(void)
{
}

bool Request::parseFromJson(const std::string& json)
{
    Json::Value root;
    Json::Reader reader;
    try {
        if (!reader.parse(json, root)) {
            LOG(ERROR) << "Invalid json request: " << json;
            return false;
        }
        Json::Value jsonUser = root.get("user", "");
        m_user = jsonUser.asString();
        Json::Value jsonPassword = root.get("pwd", "");
        m_password = jsonPassword.asString();
        LOG_IF(!m_user.empty(), INFO) << "Request received by [" << m_user << "]";
    } catch (...) {
        return false;
    }
    makeValid();
    return true;
}

bool Request::valid(void) const
{
    return m_valid;
}

const char* Request::lastError() const
{
    return m_lastError;
}

void Request::setError(const char *error)
{
    m_valid = false;
    m_lastError = error;
}

void Request::makeValid(void)
{
    m_valid = true;
    m_lastError = "";
}

bool Request::checkPermissions(Credentials *credentials) const
{
    return credentials->check(m_user, m_password, convertRequestTypeToPermissions(type()));
}

const std::string& Request::jsonRequest(void) const
{
    return m_jsonRequest;
}
