#ifndef SENSORINFODIALOG_H
#define SENSORINFODIALOG_H

#include <map>
#include <string>
#include <QDialog>
#include <iostream>
#include <algorithm>
#include <updatesensorinfothread.h>

#include <SmartDevice.h>
#include <RoutineThread.h>

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

    void on_cbRoutines_2_currentIndexChanged(const QString &arg1);

    void on_toolButton_clicked();

private:
    Ui::SensorInfoDialog *ui;
    SmartDeviceType deviceType;
    std::map<int, routine::Routine> routines;
    std::unique_ptr<UpdateSensorInfoThread> sensorThread;

    void updateRoutines();
    void setLampInfo(std::vector<HistoryData> history);
};

#endif // SENSORINFODIALOG_H
