#ifndef SENSORINFODIALOG_H
#define SENSORINFODIALOG_H

#include <string>
#include <QDialog>
#include <updatesensorinfothread.h>

#include <SmartDevice.h>

namespace Ui {
class SensorInfoDialog;
}

class SensorInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorInfoDialog(QWidget *parent = nullptr, std::string _name = "", SmartDeviceType deviceType = SmartDeviceType::SmartLamp);
    ~SensorInfoDialog();

    void destroyThread();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    SmartDeviceType deviceType;
    Ui::SensorInfoDialog *ui;
    std::unique_ptr<UpdateSensorInfoThread> sensorThread;

    void setLampInfo(std::vector<HistoryData> history);
};

#endif // SENSORINFODIALOG_H
