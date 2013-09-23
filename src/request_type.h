#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H

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
private:
    RequestTypeHelper(void);
    RequestTypeHelper(const RequestTypeHelper&);
    RequestTypeHelper& operator=(const RequestTypeHelper&);
};

#endif // REQUESTTYPE_H
