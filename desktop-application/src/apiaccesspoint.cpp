#include "apiaccesspoint.h"

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::map<std::string, std::string> getBody(std::string bodyStr) {
    std::map<std::string, std::string> resultDict;

    if (bodyStr.size() > 2) {
        auto body = split(bodyStr, ",");

        for (auto &s : body) {
            auto pairs = split(s, ":");

            if (pairs.size() == 2) {
                resultDict[pairs[0].substr(1, pairs[0].size() - 2)] = pairs[1].substr(1, pairs[1].size() - 2);
            }
        }
    }

    return resultDict;
}

void APIAccessPoint::logOut(std::string &requestMessage, int &statusRequest)
{
    statusRequest = -1;
    requestMessage = "ERROR";

    try {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request(apiServerIP + "auth/logout");

        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};
        std::map<std::string, std::string> parameters = {{"token", token}};

        // send a get request
        const http::Response response = request.send("GET", parameters, headers);

        auto body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));

        if (body.find("message") != body.end()) requestMessage = body["message"];

        if (body.find("status") != body.end()) {
            statusRequest = atoi(body["status"].c_str());

            if (statusRequest == 200) {
                if (body.find("content") != body.end()) { token = ""; }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

void APIAccessPoint::signIn(std::string email, std::string password, std::string &requestMessage, int &statusRequest)
{
    statusRequest = -1;
    requestMessage = "ERROR";

    try {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request(apiServerIP + "auth/login");

        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};
        std::map<std::string, std::string> parameters = {{"email", email}, {"password", password}};

        // send a get request
        const http::Response response = request.send("GET", parameters, headers);

        auto body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));

        if (body.find("message") != body.end()) requestMessage = body["message"];

        if (body.find("status") != body.end()) {
            statusRequest = atoi(body["status"].c_str());

            if (statusRequest == 200) {
                if (body.find("content") != body.end()) {
                    token = body["content"];
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

void APIAccessPoint::signUp(std::string name, std::string email, std::string password, std::string &requestMessage, int &statusRequest)
{
    statusRequest = -1;
    requestMessage = "ERROR";

    try {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request(apiServerIP + "auth/register");

        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};
        std::map<std::string, std::string> parameters = {{"name", name}, {"email", email}, {"password", password}};

        // send a get request
        const http::Response response = request.send("POST", parameters, headers);

        auto body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));

        if (body.find("message") != body.end()) requestMessage = body["message"];

        if (body.find("status") != body.end()) {
            statusRequest = atoi(body["status"].c_str());
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

void APIAccessPoint::passwordReset(std::string email, std::string &requestMessage, int &statusRequest)
{
    statusRequest = -1;
    requestMessage = "ERROR";

    try {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request(apiServerIP + "auth/reset");

        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};
        std::map<std::string, std::string> parameters = {{"email", email}};

        // send a get request
        const http::Response response = request.send("PUT", parameters, headers);

        auto body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));

        if (body.find("message") != body.end()) requestMessage = body["message"];

        if (body.find("status") != body.end()) {
            statusRequest = atoi(body["status"].c_str());
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

std::vector<std::string> APIAccessPoint::sensorAvailable(std::string &requestMessage, int &statusRequest)
{
    statusRequest = -1;
    requestMessage = "ERROR";
    std::vector<std::string> sensors;

    try {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request(apiServerIP + "sensors/available-sensors");

        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};

        // send a get request
        std::map<std::string, std::string> parameters = {{"token", token}};

        const http::Response response = request.send("GET", parameters, headers);

        auto body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));

        if (body.find("message") != body.end()) requestMessage = body["message"];

        if (body.find("status") != body.end()) {
            statusRequest = atoi(body["status"].c_str());

            if (statusRequest == 200) {
                if (body.find("content") != body.end()) {
                    sensors = split(body["content"], "&");
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

    return sensors;
}

std::string APIAccessPoint::getSensorStatus(std::string sensorName, std::string &requestMessage, int &statusRequest)
{
    statusRequest = -1;
    std::string value;
    requestMessage = "ERROR";

    try {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request(apiServerIP + "sensors/get-sensor-status");

        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};

        // send a get request
        std::map<std::string, std::string> parameters = {{"token", token}, {"name", sensorName}};

        const http::Response response = request.send("GET", parameters, headers);

        auto body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));

        if (body.find("message") != body.end()) requestMessage = body["message"];

        if (body.find("status") != body.end()) {
            statusRequest = atoi(body["status"].c_str());

            if (statusRequest == 200) {
                if (body.find("content") != body.end()) {
                    value = body["content"];
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

    return value;
}

void APIAccessPoint::setSensorStatus(std::string sensorName, std::string newStatus, std::string &requestMessage, int &statusRequest)
{
    statusRequest = -1;
    requestMessage = "ERROR";

    try {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request(apiServerIP + "sensors/set-sensor-status");

        std::vector<std::string> headers = {"Content-Type: application/x-www-form-urlencoded"};

        // send a get request
        std::map<std::string, std::string> parameters = {{"token", token}, {"name", sensorName}, {"status", newStatus}};

        const http::Response response = request.send("PUT", parameters, headers);

        auto body = getBody(std::string(response.body.begin() + 1, response.body.end() - 2));

        if (body.find("message") != body.end()) requestMessage = body["message"];

        if (body.find("status") != body.end()) {
            statusRequest = atoi(body["status"].c_str());
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}
