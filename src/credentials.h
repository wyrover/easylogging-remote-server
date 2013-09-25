#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <string>
#include <unordered_map>
#include "easylogging++.h"
#include "request_type.h"

enum class Permissions : unsigned short {
    None = 0,
    WriteLogs = 1,
    NewLogger = 2,
    ConfigurationUpdate = 4,
    RunCommand = 8,
    All = 16,
    Unknown = 1010
};

class PermissionsHelper {
public:
    static Permissions convertRequestTypeShortToPermissions(unsigned short requestTypeShort);
    static const char* convertPermissionsToString(const Permissions& permissions);
private:
    PermissionsHelper(void);
    PermissionsHelper(const PermissionsHelper&);
    PermissionsHelper& operator=(const PermissionsHelper&);
};


class CommandLineArgs;

///
/// @brief Responsible for server credentials
///
class Credentials : public el::Loggable
{
public:
    typedef std::string UsersHashMapKey;
    typedef std::pair<std::string, unsigned short> UsersHashMapValue;
    typedef std::unordered_map<UsersHashMapKey, UsersHashMapValue> UsersHashMap;

    static const char* kUsersParam;
    static const char* kPassKeyParam;

    explicit Credentials(CommandLineArgs* commandLineArgs);

    inline const UsersHashMap& users(void) { return m_users; }
    inline int passKey(void) { return m_passKey; }
    inline bool valid(void) { return m_valid; }
    bool check(const std::string& username, const std::string& password, const Permissions& permissions = Permissions::All) const;
    virtual void log(std::ostream&) const;
    std::string getPermissions(const std::string& username) const;
private:
    UsersHashMap m_users;
    int m_passKey;
    bool m_valid;

    ///
    /// @brief parseUsers Parses usernames/password and stores into m_users hashmap
    /// @param usersStr Taken from param kUsersParam, format is something like: [me:mypass=2,john:pass1=1]
    ///
    void parseUsers(const char* usersStr);
};

#endif // CREDENTIALS_H
