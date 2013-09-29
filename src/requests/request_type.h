#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H

#include <string>

///
/// @brief Type of request received by client
///
enum class RequestType : unsigned short {
    WriteLogs = 1,
    NewLogger = 2,
    ConfigurationUpdate = 4,
    FlagsUpdate = 8,
    Unknown = 1010
};

class JsonPacket;

class RequestTypeHelper {
public:
    static const char* convertToString(const RequestType& requestType);
    static RequestType convertFromString(const char* requestTypeStr);
    static unsigned short convertToShort(const RequestType& requestType);
    static RequestType convertFromShort(unsigned short requestTypeShort);
    static RequestType findRequestTypeFromJson(JsonPacket* json);
private:
    RequestTypeHelper(void);
    RequestTypeHelper(const RequestTypeHelper&);
    RequestTypeHelper& operator=(const RequestTypeHelper&);
};

#endif // REQUESTTYPE_H
