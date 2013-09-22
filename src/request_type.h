#ifndef REQUESTTYPE_H
#define REQUESTTYPE_H

enum RequestType : unsigned short {
    WriteLogs = 1,
    NewLogger = 2,
    ConfigurationUpdate = 3,
    Unknown = 1010
};

class RequestTypeHelper {
public:
    static const char* convertToString(const RequestType& requestType);
    static RequestType convertFromString(const char* requestTypeStr);
};

#endif // REQUESTTYPE_H
