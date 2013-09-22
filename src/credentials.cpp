#include "credentials.h"
#include <cstring>
#include <sstream>
#include <utility>

const char* Credentials::kUsersParam = "--users";
const char* Credentials::kPassKeyParam = "--passkey";


Credentials::Credentials(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        if (i != argc - 1) {
            if (strcmp(argv[i], Credentials::kUsersParam) == 0) {
                parseUsers(argv[i + 1]);
            } else if (strcmp(argv[i], Credentials::kPassKeyParam) == 0) {
                m_passKey = atoi(argv[i + 1]);
            }
        }
    }
#ifdef SERVER_REQUIRES_PERMISSION
#   ifndef SERVER_PASSKEY
#      error "Please define integer based SERVER_PASSKEY macro with value in order to user permissions"
#   else
    // If we have server passkey, our credentials are only valid when the passkey matches
    m_valid = SERVER_PASSKEY == m_passKey;
    LOG_IF(!m_valid, WARNING) << "Server pass key not verified successfully!";
#   endif // SERVER_PASSKEY
#else
    // Always valid
    m_valid = true;
#endif // SERVER_REQUIRES_PERMISSION
}

bool Credentials::checkCredentials(const std::string& username, const std::string& password) const
{
    if (!m_valid)
        return false;
#ifdef SERVER_REQUIRES_PERMISSION
    UsersHashMap::const_iterator it = m_users.find(username);
    if (it != m_users.end()) {
        return it->second.first == password;
    }
    return false;
#else
    // Unused warning
    (void)username;
    (void)password;
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
    bool isUsername = false;
    bool isPassword = false;
    for (; *usersStr; ++usersStr) {
        switch (*usersStr) {
        case ' ':
            break;
        case '[':
            username.str("");
            password.str("");
            isUsername = true;
            isPassword = false;
            break;
        case ':':
            isPassword = true;
            isUsername = false;
            password.str("");
            break;
        case ',':
        case ']':
            // Store and continue
            m_users.insert(std::pair<UsersHashMapKey, UsersHashMapValue>(username.str(), UsersHashMapValue(password.str(), CredentialsType::All)));
            username.str("");
            password.str("");
            isUsername = true;
            isPassword = false;
            break;
        default:
            if (isUsername) {
                username << *usersStr;
            } else if (isPassword) {
                password << *usersStr;
            }
        }
    }
}
