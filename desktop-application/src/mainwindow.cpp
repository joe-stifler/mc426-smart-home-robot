#include <mainwindow.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setlocale(LC_ALL, "C");

    ui->setupUi(this);

    setWindowTitle("Smart House Robot");

    showMaximized();

    plotData();

    addDevice(-5, -5, SmartDeviceType::SmartLamp);

    addDevice(5, 5, SmartDeviceType::SmartLamp);

    addDevice(0, 0, SmartDeviceType::SmartRobot);

    robotThread.reset(new RobotThread(smartDevices[smartDevices.size() - 1].get(), ui->openGLWidget));

    robotThread->start();
}

MainWindow::~MainWindow() {
    delete ui;

    robotThread->stop();

    while (robotThread->finished);

    robotThread->terminate();
}

void MainWindow::plotData() {
    ui->openGLWidget->setNewTexture("images/floorplan.png");
}

void MainWindow::addDevice(float x, float y, SmartDeviceType deviceType) {
    smartDevices.push_back(std::unique_ptr<SmartDevice>());

    smartDevices[smartDevices.size() - 1].reset(SmartDeviceFactory::instance().getSmartDevice(x, y, deviceType));

    ui->openGLWidget->addSmartDevice(smartDevices[smartDevices.size() - 1].get());
}
