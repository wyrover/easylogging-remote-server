#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <string>
#include <unordered_map>
#include "easylogging++.h"
/**
 * @brief Responsible for server credentials
 */
class Credentials : public el::Loggable
{
public:
    static const char* kUsersParam;
    static const char* kPassKeyParam;

    Credentials(int argc, char *argv[]);

    inline const std::unordered_map<std::string, std::string>& users(void) { return m_users; }
    inline int passKey(void) { return m_passKey; }
    inline bool valid(void) { return m_valid; }
    bool checkCredentials(const std::string& username, const std::string& password) const;
    virtual void log(std::ostream &) const;
private:
    std::unordered_map<std::string, std::string> m_users;
    int m_passKey;
    bool m_valid;

    /**
     * @brief parseUsers Parses usernames/password and stores into m_users hashmap
     * @param usersStr Taken from param kUsersParam, format is something like: [me:mypass,john:pass1]
     */
    void parseUsers(const char* usersStr);
};

#endif // CREDENTIALS_H
