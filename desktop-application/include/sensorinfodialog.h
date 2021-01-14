#ifndef SENSORINFODIALOG_H
#define SENSORINFODIALOG_H

#include <string>
#include <QDialog>
#include <updatesensorinfothread.h>

namespace Ui {
class SensorInfoDialog;
}

class SensorInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorInfoDialog(QWidget *parent = nullptr, std::string _name = "");
    ~SensorInfoDialog();

    void destroyThread();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SensorInfoDialog *ui;
    std::unique_ptr<UpdateSensorInfoThread> sensorThread;
};

#endif // SENSORINFODIALOG_H
