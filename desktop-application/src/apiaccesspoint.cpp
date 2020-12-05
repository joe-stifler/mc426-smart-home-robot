#include "apiaccesspoint.h"

APIAccessPoint::APIAccessPoint() {
    apiRequest = APIRequest("http://127.0.0.1", "5000");
}

APIAccessPoint::~APIAccessPoint() {}

void APIAccessPoint::logOut(std::string &requestMessage, int &statusRequest)
{

    std::map<std::string, std::string> parameters = {{"token", token}};

    auto body = apiRequest.get("auth/logout", parameters);

    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());

        if (statusRequest == 200) {
            if (body.find("content") != body.end()) { token = ""; }
        }
    } else statusRequest = -1;
}

void APIAccessPoint::signIn(std::string email, std::string password, std::string &requestMessage, int &statusRequest)
{
    std::map<std::string, std::string> parameters = {{"email", email}, {"password", password}};

    auto body = apiRequest.get("auth/login", parameters);

    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());

        if (statusRequest == 200) {
            if (body.find("content") != body.end()) {
                token = body["content"];

            }
        }
    } else statusRequest = -1;
}

void APIAccessPoint::signUp(std::string name, std::string email, std::string password, std::string &requestMessage, int &statusRequest)
{
    std::map<std::string, std::string> parameters = {{"name", name}, {"email", email}, {"password", password}};

    auto body = apiRequest.post("auth/register", parameters);

    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());
    } else statusRequest = -1;
}

void APIAccessPoint::passwordReset(std::string email, std::string &requestMessage, int &statusRequest)
{
    std::map<std::string, std::string> parameters = {{"email", email}};

    auto body = apiRequest.put("auth/reset", parameters);

    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());
    } else statusRequest = -1;
}

std::vector<std::string> APIAccessPoint::sensorAvailable(std::string &requestMessage, int &statusRequest)
{
    std::vector<std::string> sensors;

    std::map<std::string, std::string> parameters = {{"token", token}};

    auto body = apiRequest.get("sensors/available-sensors", parameters);

    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());

        if (statusRequest == 200) {
            if (body.find("content") != body.end()) {
                sensors = util::split(body["content"], "&");
            }
        }
    } else statusRequest = -1;

    return sensors;
}

std::string APIAccessPoint::getSensorStatus(std::string sensorName, std::string &requestMessage, int &statusRequest)
{
    std::string value;

    std::map<std::string, std::string> parameters = {{"token", token}, {"name", sensorName}};

    auto body = apiRequest.get("sensors/get-sensor-status", parameters);

    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());

        if (statusRequest == 200) {
            if (body.find("content") != body.end()) {
                value = body["content"];
            }
        }
    } else statusRequest = -1;

    return value;
}

void APIAccessPoint::setSensorStatus(std::string sensorName, std::string newStatus, std::string &requestMessage, int &statusRequest)
{
    std::map<std::string, std::string> parameters = {{"token", token}, {"name", sensorName}, {"status", newStatus}};

    auto body = apiRequest.put("sensors/set-sensor-status", parameters);

    if (body.find("message") != body.end()) requestMessage = body["message"];
    else requestMessage = "ERROR: No message sent";

    if (body.find("status") != body.end()) {
        statusRequest = atoi(body["status"].c_str());
    } else statusRequest = -1;
}
