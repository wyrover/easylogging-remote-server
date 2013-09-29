#ifndef REQUEST_FACTORY_H
#define REQUEST_FACTORY_H

#include <string>
#include <functional>

class Request;
class JsonPacket;
class Credentials;

class RequestFactory
{
public:
    static Request* buildRequest(JsonPacket* jsonPacket, Credentials *credentials);


    static void updateTarget(JsonPacket* jsonPacket, const std::string& key, const std::string& defaultVal, std::string* target, bool optionalKey = false);
    static void updateTarget(JsonPacket* jsonPacket, const std::string& key, int defaultVal, int* target, bool optionalKey = false);
private:
    RequestFactory(void);
    RequestFactory(const RequestFactory&);
    RequestFactory& operator=(const RequestFactory&);

    template <typename T, typename Func>
    static void updateTarget(JsonPacket* jsonPacket, const std::string& key, const T& defaultVal, T* target, bool optionalKey, const Func& f);
};

#endif // REQUEST_FACTORY_H
