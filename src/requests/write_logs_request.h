#ifndef WRITELOGSREQUEST_H
#define WRITELOGSREQUEST_H

#include "requests/request.h"
#include "easylogging++.h"

class WriteLogsRequest : public Request
{
public:
    static const JsonPacket::Keys kRequiredKeys;

    WriteLogsRequest(JsonPacket* jsonPacket, Credentials* credentials);
    virtual ~WriteLogsRequest(void);

    virtual inline RequestType type(void) const;
    virtual bool process(void);

    const std::string& logger(void) {
        return m_logger;
    }

    const el::Level& level(void) {
        return m_level;
    }

    const std::string& func(void) {
        return m_func;
    }

    const std::string& file(void) {
        return m_file;
    }

    int line(void) const {
        return m_line;
    }

    int vLevel(void) const {
        return m_vLevel;
    }

    const std::string& logMessage(void) {
        return m_logMessage;
    }
private:
    std::string m_logger;
    el::Level m_level;
    std::string m_func;
    std::string m_file;
    int m_line;
    int m_vLevel;
    std::string m_logMessage;
    virtual void buildFromJsonPacket(void);
};

#endif // WRITELOGSREQUEST_H
