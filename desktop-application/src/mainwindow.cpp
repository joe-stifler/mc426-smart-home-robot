#include <mainwindow.h>
#include "ui_mainwindow.h"

#include <apiaccesspoint.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setlocale(LC_ALL, "C");

    ui->setupUi(this);

    setWindowTitle("Smart House Robot");

    showMaximized();

    plotData();

    addDevice(-5, -5, SmartDeviceType::SmartLamp);

    addDevice(5, 5, SmartDeviceType::SmartLamp);

    addDevice(0, 0, SmartDeviceType::SmartRobot);

//    robotThread.reset(new RobotThread(smartDevices[smartDevices.size() - 1].get(), ui->openGLWidget));

//    robotThread->start();

    int status;
    std::string requestMessage;

    std::string name = "joe";
    std::string email = "joe@joe.com";
    std::string password = "password123";

    std::cout << "SIGN-UP" << std::endl;
    APIAccessPoint::instance().signUp(name, email, password, requestMessage, status);

    std::cout << "Status: " << status << std::endl;
    std::cout << "request message: " << requestMessage << std::endl;
    std::cout << std::endl;


    std::cout << "SIGN-IN" << std::endl;
    APIAccessPoint::instance().signIn(email, password, requestMessage, status);

    std::cout << "Status: " << status << std::endl;
    std::cout << "request message: " << requestMessage << std::endl;
    std::cout << std::endl;


    std::cout << "RESET" << std::endl;
    APIAccessPoint::instance().passwordReset(email, requestMessage, status);

    std::cout << "Status: " << status << std::endl;
    std::cout << "request message: " << requestMessage << std::endl;
    std::cout << std::endl;

    std::cout << "SENSOR AVAILABLE" << std::endl;
    auto sensors = APIAccessPoint::instance().sensorAvailable(requestMessage, status);

    std::cout << "Status: " << status << std::endl;
    std::cout << "request message: " << requestMessage << std::endl;

    for (auto &s : sensors) {
        std::cout << s << std::endl;
    }
    std::cout << std::endl;

    std::cout << "GET SENSOR STATUS" << std::endl;
    auto value = APIAccessPoint::instance().getSensorStatus("luz1", requestMessage, status);

    std::cout << "Status: " << status << std::endl;
    std::cout << "request message: " << requestMessage << std::endl;

    std::cout << "Value: " << value << std::endl;
    std::cout << std::endl;

    std::cout << "SET SENSOR STATUS" << std::endl;
    APIAccessPoint::instance().setSensorStatus("luz1", std::to_string(-4230), requestMessage, status);

    std::cout << "Status: " << status << std::endl;
    std::cout << "request message: " << requestMessage << std::endl;
    std::cout << std::endl;
}

MainWindow::~MainWindow() {
    delete ui;

//    robotThread->stop();

//    while (robotThread->finished);

//    robotThread->terminate();
}

void MainWindow::plotData() {
    ui->openGLWidget->setNewTexture("images/floorplan.png");
}

void MainWindow::addDevice(float x, float y, SmartDeviceType deviceType) {
    smartDevices.push_back(std::unique_ptr<SmartDevice>());

    smartDevices[smartDevices.size() - 1].reset(SmartDeviceFactory::instance().getSmartDevice(x, y, deviceType));

    ui->openGLWidget->addSmartDevice(smartDevices[smartDevices.size() - 1].get());
}
