#include "apiaccesspoint.h"

APIAccessPoint::APIAccessPoint() {
    apiRequest = APIRequest("http://127.0.0.1", "5000");

    std::ifstream tokenFile;

     // std::ios::app is the open mode "append" meaning
     // new data will be written to the end of the file.
     tokenFile.open(TOKEN_FILE);

     if (tokenFile.good()) {
         tokenFile >> token;

         tokenFile.close();
     }
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

    token = "";

    remove(TOKEN_FILE);
}

void APIAccessPoint::signIn(std::string email, std::string password, std::string &requestMessage, int &statusRequest) {
    std::map<std::string, std::string> parameters = {{"email", email}, {"password", password}};

    auto body = apiRequest.get("auth/login", parameters);

    if (checkBody(requestMessage, statusRequest, body))
        if (body.find("content") != body.end()) {
            token = body["content"];

            std::ofstream tokenFile;

            remove(TOKEN_FILE);

            // std::ios::app is the open mode "append" meaning
            // new data will be written to the end of the file.
            tokenFile.open(".token.txt", std::ios::app);

            if (tokenFile.good()) {
                tokenFile << token;

                tokenFile.close();
            }
        }
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

std::vector<HistoryData> APIAccessPoint::sensorHistory(std::string sensorName, std::string &requestMessage, int &statusRequest)
{
    std::map<std::string, std::string> parameters = {{"token", token}, {"name", sensorName}};

    auto body = apiRequest.get("sensors/get-sensor-history", parameters);

    if (checkBody(requestMessage, statusRequest, body))
        if (body.find("content") != body.end()) {
            auto rawVector = util::split(body["content"], "&");

            std::vector<HistoryData> history;

            for (auto &r : rawVector) {
                history.push_back(HistoryData(r));
            }

            return history;
        }

    return std::vector<HistoryData>();
}
