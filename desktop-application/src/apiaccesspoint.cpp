#include "apiaccesspoint.h"

APIAccessPoint::APIAccessPoint() {
    apiRequest = APIRequest("http://127.0.0.1", "5000");
}

APIAccessPoint::~APIAccessPoint() {}

bool APIAccessPoint::checkBody(std::string &requestMessage, int &statusRequest, std::map<std::string, std::string> &body) {
    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());

        if (statusRequest == 200) {
            return true;
        }
    } else statusRequest = -1;

    return false;
}

void APIAccessPoint::logOut(std::string &requestMessage, int &statusRequest) {
    std::map<std::string, std::string> parameters = {{"token", token}};

    auto body = apiRequest.get("auth/logout", parameters);

    if (checkBody(requestMessage, statusRequest, body))
        if (body.find("content") != body.end()) token = "";
}

void APIAccessPoint::signIn(std::string email, std::string password, std::string &requestMessage, int &statusRequest) {
    std::map<std::string, std::string> parameters = {{"email", email}, {"password", password}};

    auto body = apiRequest.get("auth/login", parameters);

    if (checkBody(requestMessage, statusRequest, body))
        if (body.find("content") != body.end()) token = body["content"];
}

void APIAccessPoint::signUp(std::string name, std::string email, std::string password, std::string &requestMessage, int &statusRequest) {
    std::map<std::string, std::string> parameters = {{"name", name}, {"email", email}, {"password", password}};

    auto body = apiRequest.post("auth/register", parameters);

    checkBody(requestMessage, statusRequest, body);
}

void APIAccessPoint::passwordReset(std::string email, std::string &requestMessage, int &statusRequest) {
    std::map<std::string, std::string> parameters = {{"email", email}};

    auto body = apiRequest.put("auth/reset", parameters);

    checkBody(requestMessage, statusRequest, body);
}

std::vector<std::string> APIAccessPoint::sensorAvailable(std::string &requestMessage, int &statusRequest) {
    std::map<std::string, std::string> parameters = {{"token", token}};

    auto body = apiRequest.get("sensors/available-sensors", parameters);

    if (checkBody(requestMessage, statusRequest, body))
        if (body.find("content") != body.end()) return util::split(body["content"], "&");

    return std::vector<std::string>();
}

std::string APIAccessPoint::getSensorStatus(std::string sensorName, std::string &requestMessage, int &statusRequest) {
    std::map<std::string, std::string> parameters = {{"token", token}, {"name", sensorName}};

    auto body = apiRequest.get("sensors/get-sensor-status", parameters);

    if (checkBody(requestMessage, statusRequest, body))
        if (body.find("content") != body.end()) return body["content"];

    return std::string();
}

void APIAccessPoint::setSensorStatus(std::string sensorName, std::string newStatus, std::string &requestMessage, int &statusRequest)
{
    std::map<std::string, std::string> parameters = {{"token", token}, {"name", sensorName}, {"status", newStatus}};

    auto body = apiRequest.put("sensors/set-sensor-status", parameters);

    checkBody(requestMessage, statusRequest, body);
}
