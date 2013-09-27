#include "request.h"
#include "easylogging++.h"
#include "credentials.h"
#include "request_type.h"
#include "json_packet.h"

Request::Request(JsonPacket* json) :
    m_jsonPacket(json)
{
    setLastError("");
    setValid(true);
    parseFromJson(jsonPacket());
}

Request::~Request(void)
{
}

bool Request::parseFromJson(JsonPacket* json)
{
    m_user = json->getString("user", "");
    m_password = json->getString("pwd", "");
    LOG_IF(!m_user.empty(), INFO) << "Request received by [" << m_user << "]";
    return true;
}

bool Request::userHasPermissions(Credentials* credentials) const
{
    return credentials->check(m_user, m_password, PermissionsHelper::convertRequestTypeShortToPermissions(RequestTypeHelper::convertToShort(type())));
}
