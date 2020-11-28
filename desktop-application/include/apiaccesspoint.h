#ifndef APIACCESSPOINT_H
#define APIACCESSPOINT_H

#include <vector>
#include <string>
#include <iostream>

#include <HTTPRequest.h>

class APIAccessPoint {
private:
    std::string token = "";
    std::string apiServerIP = "http://127.0.0.1:5000/";

    APIAccessPoint() {

    }

    ~APIAccessPoint() {}

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
};

#endif // APIACCESSPOINT_H
