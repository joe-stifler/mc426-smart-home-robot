#include "sensorinfodialog.h"
#include "ui_sensorinfodialog.h"

#include <QMessageBox>
#include <apiaccesspoint.h>
#include <exception>

SensorInfoDialog::SensorInfoDialog(QWidget *parent, std::string _name) :
    QDialog(parent),
    ui(new Ui::SensorInfoDialog)
{
    ui->setupUi(this);

    setWindowTitle("Sensor Info Dialog");

    ui->edit_sensor_name->setText(QString::fromStdString(_name));

    sensorThread.reset(new UpdateSensorInfoThread(_name, ui->edit_current_value));

    sensorThread->start();
}

void SensorInfoDialog::destroyThread() {
    try {
        if (sensorThread) {
            sensorThread->stop();

            while (sensorThread->isRunning());

            sensorThread.release();
        }
    } catch (std::exception& e) { }
}

SensorInfoDialog::~SensorInfoDialog()
{
    destroyThread();

    delete ui;
}

void SensorInfoDialog::on_pushButton_clicked()
{
    int statusRequest;
    std::string requestMessage;

    APIAccessPoint::instance().setSensorStatus(ui->edit_sensor_name->text().toStdString(), ui->edit_new_value->text().toStdString(), requestMessage, statusRequest);

    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(requestMessage));
    msgBox.exec();
}
