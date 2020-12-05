#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include <Util.h>
#include <HTTPRequest.h>

class APIRequest {
private:
    std::string apiServerIP;

    std::map<std::string, std::string> getBody(std::string bodyStr);

public:
    APIRequest();

    APIRequest(std::string _apiServerIP, std::string _apiServerPort);

    std::map<std::string, std::string> get(const std::string& method, const std::map<std::string, std::string>& parameters);

    std::map<std::string, std::string> post(const std::string& method, const std::map<std::string, std::string>& parameters);

    std::map<std::string, std::string> put(const std::string& method, const std::map<std::string, std::string>& parameters);
};

#endif // APIREQUEST_H
