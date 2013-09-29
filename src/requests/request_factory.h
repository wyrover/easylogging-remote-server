#ifndef REQUEST_FACTORY_H
#define REQUEST_FACTORY_H

class Request;
class JsonPacket;
class Credentials;

class RequestFactory
{
public:
    static Request* buildRequest(JsonPacket* jsonPacket, Credentials *credentials);
private:
    RequestFactory(void);
    RequestFactory(const RequestFactory&);
    RequestFactory& operator=(const RequestFactory&);
};

#endif // REQUEST_FACTORY_H
