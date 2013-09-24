#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H

#include <string>

///
/// @brief Type of request received by client
/// @detail Do not make it enum class because Intel C++ does not allow switch over it
///
enum RequestType : unsigned short {
    WriteLogs = 1,
    NewLogger = 2,
    ConfigurationUpdate = 4,
    Unknown = 1010
};

class RequestTypeHelper {
public:
    static const char* convertToString(const RequestType& requestType);
    static RequestType convertFromString(const char* requestTypeStr);
    static RequestType findRequestTypeFromJson(const std::string& json);
private:
    RequestTypeHelper(void);
    RequestTypeHelper(const RequestTypeHelper&);
    RequestTypeHelper& operator=(const RequestTypeHelper&);
};

#endif // REQUESTTYPE_H
