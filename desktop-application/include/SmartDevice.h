#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <string>

enum SmartDeviceType : char {
    SmartRobot,
    SmartLamp
};

struct SmartDevice {
    float x;
    float y;
    float dx;
    float dy;
    std::string path;

    SmartDevice() {}

    SmartDevice(float _x, float _y, float _dx, float _dy, std::string _path) {
        x = _x;
        y = _y;
        dx = _dx;
        dy = _dy;
        path = _path;
    }
};

class SmartDeviceFactory {
private:
    SmartDeviceFactory() {}

    ~SmartDeviceFactory() {}

public:
    SmartDeviceFactory(SmartDeviceFactory&&) = delete;
    SmartDeviceFactory(const SmartDeviceFactory&) = delete;
    SmartDeviceFactory& operator=(const SmartDeviceFactory&) = delete;
    SmartDeviceFactory& operator=(SmartDeviceFactory&&) = delete;

    static SmartDeviceFactory& instance() {
        static SmartDeviceFactory INSTANCE;
        return INSTANCE;
    }

    SmartDevice *getSmartDevice(float x, float y, SmartDeviceType deviceType) {
        switch(deviceType) {
            case SmartDeviceType::SmartRobot:
                return new SmartDevice(x, y, 0.07, 0.12, "icons/smart_robot.png");

            case SmartDeviceType::SmartLamp:
                return new SmartDevice(x, y, 0.1, 0.15, "icons/smart_lamp.png");
        }

        return new SmartDevice(x, y, 0, 0, "");
    }
};

#endif // SMARTDEVICE_H
