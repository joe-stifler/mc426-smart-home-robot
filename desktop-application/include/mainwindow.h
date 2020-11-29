#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include <QThread>
#include <unistd.h>

#include <QCoreApplication>
#include <QEventLoop>
#include <QTime>
#include <SmartDevice.h>
#include <openglclass.h>

#include <QFileDialog>

#include <apiaccesspoint.h>
#include <getsensorsdialog.h>

class RobotThread : public QThread
{
    Q_OBJECT
private:

    void run() {
        while (status) {
            for (int i = 0; i < 100; ++i) {
                smartDevice->x = 5.0f / 100.0f * (float) i;

                openglclass->update();

                QTime dieTime= QTime::currentTime().addMSecs(25);

                while (QTime::currentTime() < dieTime)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                openglclass->update();
            }

            for (int i = 0; i < 100; ++i) {
                smartDevice->y = -5.0 / 100.0f * i;

                openglclass->update();

                QTime dieTime= QTime::currentTime().addMSecs(25);

                while (QTime::currentTime() < dieTime)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                openglclass->update();
            }

            for (int i = 0; i < 200; ++i) {
                smartDevice->x = 5.0f - 5.0 / 200.0f * i;

                openglclass->update();

                QTime dieTime= QTime::currentTime().addMSecs(15);

                while (QTime::currentTime() < dieTime)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                openglclass->update();
            }

            for (int i = 0; i < 200; ++i) {
                smartDevice->y = -5.0f + 5.0 / 200.0f * i;

                openglclass->update();

                QTime dieTime= QTime::currentTime().addMSecs(15);

                while (QTime::currentTime() < dieTime)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                openglclass->update();
            }
        }

        finished = false;
    }

public:
    bool status = true;
    bool finished = true;
    SmartDevice *smartDevice;
    OpenGLClass *openglclass;

    RobotThread(SmartDevice *_smartDevice, OpenGLClass *_openglclass) {
        smartDevice = _smartDevice;
        openglclass = _openglclass;
    }

    ~RobotThread() {}

    void setMessage(const QString &_message) {}

    void stop() {
        status = false;
    }
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void signIn();
    void signOut();
    void signUp();
    void resetPassword();
    void closeWindow();
    void openFloorplanButton();
    void addSmartDevice(float x, float y);

private:
    Ui::MainWindow *ui;

    std::vector<std::unique_ptr<SmartDevice>> smartDevices;

    int height, width, nrChannels;

    void plotData(std::string flooplanFile);

    std::unique_ptr<RobotThread> robotThread;
};
#endif // MAINWINDOW_H
