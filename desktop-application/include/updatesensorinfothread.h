#ifndef UPDATESENSORINFOTHREAD_H
#define UPDATESENSORINFOTHREAD_H

#include <QThread>
#include <unistd.h>

#include <QCoreApplication>
#include <QEventLoop>
#include <QLineEdit>
#include <QTime>
#include <apiaccesspoint.h>

class UpdateSensorInfoThread : public QThread
{
    Q_OBJECT
private:
    void run() {
        while (status) {
            QTime dieTime= QTime::currentTime().addMSecs(1000);

            int statusRequest;
            std::string requestMessage;

            std::string value = APIAccessPoint::instance().getSensorStatus(sensorName, requestMessage, statusRequest);

            currentValue->setText(QString::fromStdString(value));

            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        finished = false;
    }

public:
    bool status = true;
    bool finished = true;
    std::string sensorName;
    QLineEdit *currentValue;

    UpdateSensorInfoThread(std::string _sensorName, QLineEdit *_currentValue)
    {
        sensorName = _sensorName;
        currentValue = _currentValue;
    }


    void setMessage(const QString &_message) {}

    void stop() {
        status = false;
    }
};

#endif // UPDATESENSORINFOTHREAD_H
