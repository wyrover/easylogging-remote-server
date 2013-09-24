#include "request.h"

Request::Request(const std::string& jsonRequest) :
    m_jsonRequest(jsonRequest)
{
    parseFromJson(m_jsonRequest);
}

bool Request::parseFromJson(const std::string& json)
{
    return false;
}
