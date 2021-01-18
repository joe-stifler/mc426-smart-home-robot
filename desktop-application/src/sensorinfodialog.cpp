#include "sensorinfodialog.h"
#include "ui_sensorinfodialog.h"

#include <QMessageBox>
#include <apiaccesspoint.h>
#include <exception>

SensorInfoDialog::SensorInfoDialog(QWidget *parent, std::string _name, SmartDeviceType _deviceType) :
    QDialog(parent),
    ui(new Ui::SensorInfoDialog)
{
    ui->setupUi(this);

    deviceType = _deviceType;

    setWindowTitle("Sensor Info Dialog");

    ui->edit_sensor_name->setText(QString::fromStdString(_name));

    sensorThread.reset(new UpdateSensorInfoThread(_name, ui->edit_current_value));

    sensorThread->start();

    switch(_deviceType) {
        case SmartDeviceType::SmartLamp:
            ui->edit_new_value->setEnabled(true);
            ui->pushButton->setEnabled(true);
            break;
        case SmartDeviceType::SmartEnergy:
            break;
        case SmartDeviceType::SmartAir:
                break;
        case SmartDeviceType::SmartPresence:
            break;
        case SmartDeviceType::SmartTemperature:
            break;
        case SmartDeviceType::SmartCamera:
            break;
    }

    QDateTime dateTime = QDateTime::currentDateTime();

    ui->timeEdit->setTime(dateTime.time());
    ui->calendarWidget->setSelectedDate(dateTime.date());

    updateRoutines();
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

void SensorInfoDialog::updateRoutines() {
    int counter = 0;

    routines = routine::RoutineAccessPoint::instance().getRoutines();

    ui->cbRoutines_2->clear();

    for (auto &r : routines) {
        if (r.sensorName == ui->edit_sensor_name->text().toStdString()) {
            switch (r.routineType) {
                case routine::NoRepeat:
                    if (!r.checked)
                        ui->cbRoutines_2->addItem(QString::number(counter));

                    break;

                case routine::Daily:
                    ui->cbRoutines_2->addItem(QString::number(counter));

                    break;

                case routine::Weekly:
                    ui->cbRoutines_2->addItem(QString::number(counter));

                    break;
                case routine::Monthly:
                    ui->cbRoutines_2->addItem(QString::number(counter));

                    break;

                default:
                    break;
            }
        }

        counter++;
    }
}

void SensorInfoDialog::on_pushButton_clicked()
{
    QTime time = ui->timeEdit->time();
    QDate date = ui->calendarWidget->selectedDate();

    routine::RoutineType routineType;

    switch (ui->cbFrequency->currentIndex()) {
        case 0:
            routineType = routine::RoutineType::NoRepeat;
            break;
        case 1:
            routineType = routine::RoutineType::Daily;
            break;
        case 2:
            routineType = routine::RoutineType::Weekly;
            break;
        case 3:
            routineType = routine::RoutineType::Monthly;
            break;
        default:
            routineType = routine::RoutineType::NoRepeat;
    }

    routine::RoutineAccessPoint::instance().addRountine(ui->edit_sensor_name->text().toStdString(), ui->edit_new_value->text().toStdString(), QDateTime(date, time), routineType);

    ui->edit_new_value->setText("");

    updateRoutines();
}

void SensorInfoDialog::on_pushButton_2_clicked()
{
    int statusRequest;
    std::string requestMessage;

    std::vector<HistoryData> history;
    std::vector<HistoryData> historyAux = APIAccessPoint::instance().sensorHistory(ui->edit_sensor_name->text().toStdString(), requestMessage, statusRequest);

    for (auto &h : historyAux) {
        long long int minSecsAllowed = 0;

        switch (ui->cb_period->currentIndex()) {
            case 0: // 6 hours
                minSecsAllowed = 60 * 60 * 6;

                break;
            case 1: // 12 hours
                minSecsAllowed = 60 * 60 * 12;

                break;
            case 2: // 1 day
                minSecsAllowed = 60 * 60 * 24 * 1;

                break;
            case 3: // 2 days
                minSecsAllowed = 60 * 60 * 24 * 2;

                break;
            case 4: // 4 days
                minSecsAllowed = 60 * 60 * 24 * 4;

                break;
            case 5: // 7 days
                minSecsAllowed = 60 * 60 * 24 * 7 * 1;

                break;
            case 6: // 2 weeks
                minSecsAllowed = 60 * 60 * 24 * 7 * 2;
                break;
            case 7: // 4 weeks
                minSecsAllowed = 60 * 60 * 24 * 7 * 4;

                break;
            default: // 2 month
                minSecsAllowed = 60 * 60 * 24 * 7 * 4 * 1;

                break;
        }

        if ((QDateTime::currentSecsSinceEpoch() - h.toQDateTime().toSecsSinceEpoch()) <= minSecsAllowed) {
            history.push_back(h);
        }
    }

    ui->cb_values->clear();

    for (auto &h : history) {
        std::string line = "[" + h.month() + "/" + h.day() + "/" + h.year() + " "
                + h.hour() + ":" + h.minute() + ":" + h.second() + "] [Value = " + std::to_string(atoi(h.value().c_str())) + "]";

        ui->cb_values->addItem(QString::fromStdString(line));
    }

    switch(deviceType) {
        case SmartDeviceType::SmartLamp:
            setLampInfo(history);
            break;
        case SmartDeviceType::SmartEnergy:
            break;
        case SmartDeviceType::SmartAir:
                break;
        case SmartDeviceType::SmartPresence:
            break;
        case SmartDeviceType::SmartTemperature:
            break;
        case SmartDeviceType::SmartCamera:
            break;
    }
}

void SensorInfoDialog::setLampInfo(std::vector<HistoryData> history)
{
    bool applied = false;
    long long int seconds_on = 0;
    long long int seconds_off = 0;
    HistoryData lastHistory;

    if (history.size() > 0) {
        for (auto &h : history) {
            if (applied) {
                if (atoi(lastHistory.value().c_str()) == 0) {
                    seconds_off += (h.toQDateTime().toSecsSinceEpoch() - lastHistory.toQDateTime().toSecsSinceEpoch());
                } else {
                    seconds_on += (h.toQDateTime().toSecsSinceEpoch() - lastHistory.toQDateTime().toSecsSinceEpoch());
                }
            }

            applied = true;
            lastHistory = h;
        }

        if (atoi(lastHistory.value().c_str()) == 0) {
            seconds_off += (QDateTime::currentSecsSinceEpoch() - lastHistory.toQDateTime().toSecsSinceEpoch());
        } else {
            seconds_on += (QDateTime::currentSecsSinceEpoch() - lastHistory.toQDateTime().toSecsSinceEpoch());
        }
    }

    float consumption = ui->cb_bulb_type->value() * (float(seconds_on) / (60.0f * 60.0f));

    consumption /= 1000.0f;

    ui->label_consumption->setText(QString::number(consumption) + " kWh");
    ui->label_time_on->setText(QString::number(seconds_on) + "s");
    ui->label_time_off->setText(QString::number(seconds_off) + "s");
}

void SensorInfoDialog::on_cbRoutines_2_currentIndexChanged(const QString &arg1)
{
    int index = atoi(arg1.toStdString().c_str());
    if (index < routines.size()) {
        auto r = routines[index];

        ui->dateTimeRoutine->setDateTime(r.dateTime);

        switch (r.routineType) {
            case routine::NoRepeat:
                ui->routineType->setText("Doesn't repeat");

                break;

            case routine::Daily:
                ui->routineType->setText("Daily");

                break;

            case routine::Weekly:
                ui->routineType->setText("Weekly");

                break;
            case routine::Monthly:
                ui->routineType->setText("Monthly");

                break;

            default:
                break;
        }
    }
}
