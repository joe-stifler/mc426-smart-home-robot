#include <QMessageBox>
#include <mainwindow.h>
#include <sensorinfodialog.h>
#include <signindialog.h>
#include <signupdialog.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setlocale(LC_ALL, "C");

    ui->setupUi(this);

    setWindowTitle("Smart House Robot");

    showMaximized();

    plotData("images/floorplan.png");

    connect(ui->openGLWidget, SIGNAL(ClickPlot(float, float)), this, SLOT(addSmartDevice(float, float)));

    connect(ui->openGLWidget, SIGNAL(ClickSensor(SmartDevice *)), this, SLOT(showSmartDeviceInfo(SmartDevice *)));

//    signIn();

    routine::RoutineAccessPoint::instance().start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::signIn()
{
    bool valid = true;
    std::string email = "josias@gmail.com", password = "password123";

    while (valid) {
        std::unique_ptr<SignInDialog> dialog(new SignInDialog(nullptr, email, password));

        if (dialog->exec()) {
            int status;
            std::string requestMessage;

            email = dialog->getEmail();
            password = dialog->getPassword();

            APIAccessPoint::instance().signIn(email, password, requestMessage, status);

            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(requestMessage));
            msgBox.exec();

            if (status == 200) return;
        } else return;
    }
}

void MainWindow::signOut()
{
    int status;
    std::string requestMessage;

    APIAccessPoint::instance().logOut(requestMessage, status);
}

void MainWindow::signUp()
{
    bool valid = true;
    std::string email, name, password;

    while (valid) {
        std::unique_ptr<SignUpDialog> dialog(new SignUpDialog(nullptr, name, email, password));

        if (dialog->exec()) {
            int status;
            std::string requestMessage;

            name = dialog->getName();
            email = dialog->getEmail();
            password = dialog->getPassword();

            APIAccessPoint::instance().signUp(name, email, password, requestMessage, status);

            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(requestMessage));
            msgBox.exec();

            if (status == 200) {
                valid = false;
            }
        } else return;
    }

    signIn();
}

void MainWindow::resetPassword()
{

}

void MainWindow::closeWindow()
{
    QApplication::quit();
}

void MainWindow::openFloorplanButton()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Choose floorplan image"), "",
        tr("Floorplan Image (*.png);;All Files (*)")
    );

    if (fileName.toStdString() != "")
        plotData(fileName.toStdString());
}

void MainWindow::plotData(std::string flooplanFile) {
    ui->openGLWidget->setNewTexture(flooplanFile);
}

void MainWindow::addSmartDevice(float x, float y) {
    int status;
    std::string requestMessage;

    auto sensors = APIAccessPoint::instance().sensorAvailable(requestMessage, status);

    if (status == 200) {
        std::unique_ptr<GetSensorsDialog> dialog(new GetSensorsDialog(nullptr, sensors, x, y));

        if (dialog->exec()) {
            for (auto &smartDevice : dialog->getSelectedDevices()) {
                smartDevices.push_back(std::unique_ptr<SmartDevice>());

                SmartDevice *_smartDev = new SmartDevice();
                *_smartDev = smartDevice;

                smartDevices[smartDevices.size() - 1].reset(_smartDev);

                ui->openGLWidget->addSmartDevice(smartDevices[smartDevices.size() - 1].get());
            }
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(requestMessage));
        msgBox.exec();
    }
}

void MainWindow::showSmartDeviceInfo(SmartDevice *smartDev)
{
    std::unique_ptr<SensorInfoDialog> dialog(new SensorInfoDialog(nullptr, smartDev->getName(), smartDev->getType()));

    dialog->exec();

    dialog->destroyThread();
}
