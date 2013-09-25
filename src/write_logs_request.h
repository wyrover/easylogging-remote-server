#ifndef WRITELOGSREQUEST_H
#define WRITELOGSREQUEST_H

#include "request.h"
#include "easylogging++.h"

class WriteLogsRequest : public Request
{
public:
    explicit WriteLogsRequest(const std::string& jsonRequest);
    virtual ~WriteLogsRequest(void);

    virtual bool parseFromJson(const std::string& json);
    virtual inline RequestType type(void) const;
    virtual bool process(void);

    const el::Level& level(void);
    const std::string& logger(void);
    const std::string& func(void);
    const std::string& file(void);
    unsigned long int line(void) const;
    int vLevel(void) const;
    const std::string& logMessage(void);
private:
    std::string m_logger;
    el::Level m_level;
    std::string m_func;
    std::string m_file;
    unsigned long int m_line;
    int m_vLevel;
    std::string m_logMessage;
};

#endif // WRITELOGSREQUEST_H
