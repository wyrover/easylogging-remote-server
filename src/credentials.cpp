#include "credentials.h"
#include <cstring>
#include <sstream>
#include <utility>
#include "command_line_args.h"

const char* Credentials::kUsersParam = "--users";
const char* Credentials::kPassKeyParam = "--passkey";

Credentials::Credentials(CommandLineArgs* commandLineArgs)
{
    if (commandLineArgs->hasParamWithValue(Credentials::kUsersParam)) {
        parseUsers(commandLineArgs->getParamValue(Credentials::kUsersParam));
    }
    if (commandLineArgs->hasParamWithValue(Credentials::kPassKeyParam)) {
        m_passKey = atoi(commandLineArgs->getParamValue(Credentials::kPassKeyParam));
    }
#ifdef SERVER_REQUIRES_PERMISSION
#   ifndef SERVER_PASSKEY
#      error "Please define integer based SERVER_PASSKEY macro with value in order to user permissions"
#   else
    // If we have server passkey, our credentials are only valid when the passkey matches
    m_valid = SERVER_PASSKEY == m_passKey;
    CHECK(m_valid) << "Server pass key not verified successfully!";
#   endif // SERVER_PASSKEY
#else
    // Always valid
    m_valid = true;
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
    os << "Pass key: [" << (m_valid ? "" : "not ") << "verified]";
}

void Credentials::parseUsers(const char* usersStr)
{
    LOG(INFO) << "Parsing users from string: " << usersStr;
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
            VLOG(3) << "Creating permissions for [" << username.str() << "] = [" << permissions.str() << "]";
            m_users.insert(std::pair<UsersHashMapKey, UsersHashMapValue>(username.str(), UsersHashMapValue(password.str(), atoi(permissions.str().c_str()))));
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
    VLOG(3) << "Users: " << m_users;
}
