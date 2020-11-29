#include <QMessageBox>
#include <mainwindow.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setlocale(LC_ALL, "C");

    ui->setupUi(this);

    setWindowTitle("Smart House Robot");

    showMaximized();

    plotData("images/floorplan.png");

    connect(ui->openGLWidget, SIGNAL(ClickPlot(float, float)), this, SLOT(addSmartDevice(float, float)));

//    addDevice(0, 0, SmartDeviceType::SmartLamp);

//    addDevice(0.5, 0.5, SmartDeviceType::SmartLamp);


//    robotThread.reset(new RobotThread(smartDevices[smartDevices.size() - 1].get(), ui->openGLWidget));

//    robotThread->start();

    int status;
    std::string requestMessage;

    std::string name = "joe";
    std::string email = "joe@joe.com";
    std::string password = "password123";

//    std::cout << "SIGN-UP" << std::endl;
//    APIAccessPoint::instance().signUp(name, email, password, requestMessage, status);

//    std::cout << "Status: " << status << std::endl;
//    std::cout << "request message: " << requestMessage << std::endl;
//    std::cout << std::endl;


    APIAccessPoint::instance().signIn(email, password, requestMessage, status);

//    std::cout << "RESET" << std::endl;
//    APIAccessPoint::instance().passwordReset(email, requestMessage, status);

//    std::cout << "Status: " << status << std::endl;
//    std::cout << "request message: " << requestMessage << std::endl;
//    std::cout << std::endl;



//    std::cout << "GET SENSOR STATUS" << std::endl;
//    auto value = APIAccessPoint::instance().getSensorStatus("luz1", requestMessage, status);

//    std::cout << "Status: " << status << std::endl;
//    std::cout << "request message: " << requestMessage << std::endl;

//    std::cout << "Value: " << value << std::endl;
//    std::cout << std::endl;

//    std::cout << "SET SENSOR STATUS" << std::endl;
//    APIAccessPoint::instance().setSensorStatus("luz1", std::to_string(-4230), requestMessage, status);

//    std::cout << "Status: " << status << std::endl;
//    std::cout << "request message: " << requestMessage << std::endl;
//    std::cout << std::endl;
}

MainWindow::~MainWindow() {
    delete ui;

//    robotThread->stop();

//    while (robotThread->finished);

    //    robotThread->terminate();
}

void MainWindow::signIn()
{

}

void MainWindow::signOut()
{

}

void MainWindow::signUp()
{

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
    std::unique_ptr<GetSensorsDialog> dialog(new GetSensorsDialog());

    if (dialog->exec()) {
        for (auto &smartDevice : dialog->selectedSensors) {
            smartDevices.push_back(std::unique_ptr<SmartDevice>());

            smartDevices[smartDevices.size() - 1].reset(SmartDeviceFactory::instance().getSmartDevice(x, y, smartDevice));

            ui->openGLWidget->addSmartDevice(smartDevices[smartDevices.size() - 1].get());
        }
    }
}
