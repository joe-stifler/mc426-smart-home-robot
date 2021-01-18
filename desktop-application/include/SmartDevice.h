#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <string>

enum SmartDeviceType : char {
    SmartLamp,
    SmartEnergy,
    SmartAir,
    SmartCamera,
    SmartPresence,
    SmartTemperature
};

class SmartDevice {
    float x;
    float y;
    float dx;
    float dy;
    std::string name;
    std::string path;
    SmartDeviceType type;

public:
    SmartDevice() {}

    SmartDevice(float _x, float _y, float _dx, float _dy, std::string _path, std::string _name, SmartDeviceType _type) {
        x = _x;
        y = _y;
        dx = _dx;
        dy = _dy;
        name = _name;
        path = _path;
        type = _type;
    }

    float getX() {return x;}

    float getY() {return y;}

    float getDx() {return dx;}

    float getDy() {return dy;}

    std::string getPath() {return path;}

    std::string getName() {return name;}

    SmartDeviceType getType() {return type;}

    void setX(float _x) {x = _x;}

    void setY(float _y) {y = _y;}
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

    SmartDevice getSmartDevice(float x, float y, SmartDeviceType deviceType, std::string name) {
        switch(deviceType) {
            case SmartDeviceType::SmartLamp:
                return SmartDevice(x, y, 0.07, 0.1, "icons/light.png", name, deviceType);

            case SmartDeviceType::SmartEnergy:
                return SmartDevice(x, y, 0.07, 0.1, "icons/energy.png", name, deviceType);

            case SmartDeviceType::SmartAir:
                return SmartDevice(x, y, 0.07, 0.1, "icons/air.png", name, deviceType);

            case SmartDeviceType::SmartCamera:
                return SmartDevice(x, y, 0.07, 0.1, "icons/camera.png", name, deviceType);

            case SmartDeviceType::SmartPresence:
                return SmartDevice(x, y, 0.07, 0.1, "icons/presence.png", name, deviceType);

            case SmartDeviceType::SmartTemperature:
                return SmartDevice(x, y, 0.07, 0.1, "icons/temperature.png", name, deviceType);
        }

        return SmartDevice(x, y, 0, 0, "", name, deviceType);
    }
};

#endif // SMARTDEVICE_H
