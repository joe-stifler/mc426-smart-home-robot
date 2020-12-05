#include "apirequest.h"

APIRequest::APIRequest() {}

APIRequest::APIRequest(std::string _apiServerIP, std::string _apiServerPort) {
    apiServerIP = _apiServerIP + ":" + _apiServerPort + "/";
    headers = {"Content-Type: application/x-www-form-urlencoded"};
}

std::map<std::string, std::string> APIRequest::getBody(std::string bodyStr) {
    std::map<std::string, std::string> resultDict;

    if (bodyStr.size() > 2) {
        auto body = util::split(bodyStr, ",");

        for (auto &s : body) {
            auto pairs = util::split(s, ":");

            if (pairs.size() == 2) {
                resultDict[pairs[0].substr(1, pairs[0].size() - 2)] = pairs[1].substr(1, pairs[1].size() - 2);
            }
        }
    }

    return resultDict;
}

std::map<std::string, std::string> APIRequest::makeRequest(std::string requestType, const std::string &method, const std::map<std::string, std::string> &parameters) {
    std::map<std::string, std::string> body;

    try {
        http::Request request(apiServerIP + method);

        const http::Response response = request.send(requestType, parameters, headers); // send a get request

        body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

    return body;
}

std::map<std::string, std::string> APIRequest::get(const std::string &method, const std::map<std::string, std::string> &parameters) {
    return makeRequest("GET", method, parameters);
}

std::map<std::string, std::string> APIRequest::post(const std::string &method, const std::map<std::string, std::string> &parameters) {
    return makeRequest("POST", method, parameters);
}

std::map<std::string, std::string> APIRequest::put(const std::string &method, const std::map<std::string, std::string> &parameters) {
    return makeRequest("PUT", method, parameters);
}
