#ifndef APIACCESSPOINT_H
#define APIACCESSPOINT_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "HistoryData.h"
#include <apirequest.h>

#define TOKEN_FILE ".token.txt"
#define ROUNTINES_FILE ".routines.txt"

class APIAccessPoint {
private:
    std::string token = "";
    APIRequest apiRequest;

    APIAccessPoint();

    ~APIAccessPoint();

    bool checkBody(std::string &requestMessage, int &statusRequest, std::map<std::string, std::string> &body);

public:
    APIAccessPoint(APIAccessPoint&&) = delete;
    APIAccessPoint(const APIAccessPoint&) = delete;
    APIAccessPoint& operator=(const APIAccessPoint&) = delete;
    APIAccessPoint& operator=(APIAccessPoint&&) = delete;

    static APIAccessPoint& instance() {
        static APIAccessPoint INSTANCE;
        return INSTANCE;
    }

    void logOut(std::string &requestMessage, int &statusRequest);

    void signIn(std::string email, std::string password, std::string &requestMessage, int &statusRequest);

    void signUp(std::string name, std::string email, std::string password, std::string &requestMessage, int &statusRequest);

    void passwordReset(std::string email, std::string &requestMessage, int &statusRequest);

    std::vector<std::string> sensorAvailable(std::string &requestMessage, int &statusRequest);

    std::string getSensorStatus(std::string sensorName, std::string &requestMessage, int &statusRequest);

    void setSensorStatus(std::string sensorName, std::string newStatus, std::string &requestMessage, int &statusRequest);

    std::vector<HistoryData> sensorHistory(std::string sensorName, std::string &requestMessage, int &statusRequest);
};

#endif // APIACCESSPOINT_H
