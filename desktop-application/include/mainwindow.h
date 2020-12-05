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
};
#endif // MAINWINDOW_H
