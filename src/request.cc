#include "request.h"
#include <jsoncpp/json.h>
#include "easylogging++.h"
#include "credentials.h"
#include "request_type.h"

Request::Request(const std::string& json) :
    m_jsonRequest(json)
{
    setLastError("");
    setValid(true);
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
        setLastError("Error occured while parsing json request");
        setValid(false);
        return false;
    }
    setValid(true);
    return true;
}

const std::string& Request::lastError(void) const
{
    return m_lastError;
}

void Request::setLastError(const std::string& error)
{
    m_lastError = error;
}

bool Request::valid(void) const
{
    return m_valid;
}

void Request::setValid(bool isValid)
{
    m_valid = isValid;
    m_lastError = "";
}

bool Request::userHasPermissions(Credentials* credentials) const
{
    return credentials->check(m_user, m_password, PermissionsHelper::convertRequestTypeShortToPermissions(RequestTypeHelper::convertToShort(type())));
}

const std::string& Request::user(void) const
{
    return m_user;
}

const std::string& Request::jsonRequest(void) const
{
    return m_jsonRequest;
}
