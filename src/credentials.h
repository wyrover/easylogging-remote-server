#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <string>
#include <unordered_map>
#include "easylogging++.h"
#include "request_type.h"

enum class CredentialsType : unsigned short {
    None = 1,
    All = 2,
    WriteLogs = 4,
    NewLogger = 8,
    ConfigurationUpdate = 16,
    Unknown = 1010
};

///
/// @brief Responsible for server credentials
///
class Credentials : public el::Loggable
{
public:
    typedef std::string UsersHashMapKey;
    typedef std::pair<std::string, CredentialsType> UsersHashMapValue;
    typedef std::unordered_map<UsersHashMapKey, UsersHashMapValue> UsersHashMap;

    static const char* kUsersParam;
    static const char* kPassKeyParam;

    Credentials(int argc, char *argv[]);

    inline const UsersHashMap& users(void) { return m_users; }
    inline int passKey(void) { return m_passKey; }
    inline bool valid(void) { return m_valid; }
    bool checkCredentials(const std::string& username, const std::string& password) const;
    virtual void log(std::ostream &) const;
private:
    UsersHashMap m_users;
    int m_passKey;
    bool m_valid;

    ///
    /// @brief parseUsers Parses usernames/password and stores into m_users hashmap
    /// @param usersStr Taken from param kUsersParam, format is something like: [me:mypass,john:pass1]
    ///
    void parseUsers(const char* usersStr);
};

#endif // CREDENTIALS_H
