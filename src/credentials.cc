
#include <cstring>
#include <sstream>

#include "credentials.h"

const char* Credentials::kUsersParam = "--users";
const char* Credentials::kPassKeyParam = "--passkey";

Credentials::Credentials(void)
{
    if (el::Helpers::commandLineArgs()->hasParamWithValue(kUsersParam)) {
        parseUsers(el::Helpers::commandLineArgs()->getParamValue(kUsersParam));
    }
    if (el::Helpers::commandLineArgs()->hasParamWithValue(Credentials::kPassKeyParam)) {
        m_passKey = atoi(el::Helpers::commandLineArgs()->getParamValue(Credentials::kPassKeyParam));
    }
#ifdef SERVER_REQUIRES_PERMISSION
#   ifndef SERVER_PASSKEY
#      error "Please define integer based SERVER_PASSKEY macro with value in order to user permissions"
#   else
    // If we have server passkey, our credentials are only valid when the passkey matches
    m_valid = SERVER_PASSKEY == m_passKey;
    m_requireCredentials = true;
    CHECK(m_valid) << "Server pass key not verified successfully!";
#   endif // SERVER_PASSKEY
#else
    // Always valid
    m_valid = true;
    m_requireCredentials = false;
#endif // SERVER_REQUIRES_PERMISSION
}

bool Credentials::check(const std::string& username, const std::string& password, const Permissions& permissions) const
{
    if (!m_valid)
        return false;
#ifdef SERVER_REQUIRES_PERMISSION
    UsersHashMap::const_iterator it = m_users.find(username);
    if (it != m_users.end()) {
        bool validPassword = it->second.first == password;
        if (validPassword) {
            if (static_cast<Permissions>(it->second.second) == Permissions::All) {
                return true;
            }
            if (static_cast<Permissions>(it->second.second) == Permissions::None) {
                return false;
            }
            return static_cast<unsigned short>(permissions) & it->second.second;
        }
        return false;
    }
    return false;
#else
    // Unused warning
    (void)username;
    (void)password;
    (void)permissions;
    return true;
#endif
}

void Credentials::log(std::ostream& os) const
{
    os << m_users.size() << " Users; ";
    os << el::Helpers::convertTemplateToStdString(m_users);
}

std::string Credentials::getPermissions(const std::string& username) const
{
    UsersHashMap::const_iterator it = m_users.find(username);
    if (it != m_users.end()) {
        unsigned short flags = it->second.second;
        std::stringstream ss;
        for (unsigned short i = static_cast<unsigned short>(Permissions::All); ; i >>= 1) {
            if (i & flags) {
                ss << PermissionsHelper::convertPermissionsToString(static_cast<Permissions>(i)) << ", ";
            }
            if (i == 0) break;
        }
        std::string perms = ss.str();
        return perms.erase(perms.size() - 2);
    }
    return std::string();
}

void Credentials::parseUsers(const char* usersStr)
{
    VLOG(3) << "Parsing users from string: " << usersStr;
    std::stringstream username;
    std::stringstream password;
    std::stringstream permissions;
    bool isUsername = true;
    bool isPassword = false;
    bool isPermissions = false;
    for (; *usersStr; ++usersStr) {
        switch (*usersStr) {
        case ' ':
        case '[':
            break;
        case ':':
            isPassword = true;
            isUsername = false;
            isPermissions = false;
            password.str("");
            permissions.str("");
            break;
        case '=':
            isPassword = false;
            isUsername = false;
            isPermissions = true;
            permissions.str("");
            break;
        case ',':
        case ']':
            // Store and continue
            if (permissions.str().empty()) permissions << "0";
            if (m_users.find(username.str()) == m_users.end()) {
                VLOG(2) << "Creating permissions for [" << username.str() << "] = [" << permissions.str() << "]";
                m_users.insert(std::make_pair(username.str(), UsersHashMapValue(password.str(), atoi(permissions.str().c_str()))));
            } else {
                VLOG(2) << "Skipping [" << username.str() << "] as it is already registered.";
            }
            username.str("");
            password.str("");
            permissions.str("");
            isUsername = true;
            isPassword = false;
            isPermissions = false;
            break;
        default:
            if (isUsername) {
                username << *usersStr;
            } else if (isPassword) {
                password << *usersStr;
            } else if (isPermissions) {
                permissions << *usersStr;
            }
        }
    }
}

Permissions PermissionsHelper::convertRequestTypeShortToPermissions(unsigned short requestTypeShort)
{
    return (static_cast<Permissions>(RequestTypeHelper::convertFromShort(requestTypeShort)));
}

const char* PermissionsHelper::convertPermissionsToString(const Permissions& permissions)
{
    // Intel C++ does not yet support switch over strongly-typed enums so we use if-statements
    if (permissions == Permissions::WriteLogs)
        return "WRITE_LOGS";
    if (permissions == Permissions::NewLogger)
        return "NEW_LOGGER";
    if (permissions == Permissions::ConfigurationUpdate)
        return "CONFIGURATION_UPDATE";
    return "UNKNOWN";
}
