#ifndef ROUTINETHREAD_H
#define ROUTINETHREAD_H

#include <memory>
#include <string>
#include <QThread>
#include <QDateTime>
#include <QReadWriteLock>
#include <QCoreApplication>
#include <apiaccesspoint.h>

namespace routine {
    enum RoutineType : char {
        NoRepeat,
        Daily,
        Weekly,
        Monthly
    };

    struct Routine {
        std::string status;
        QDateTime dateTime;
        bool checked = false;
        std::string sensorName;
        RoutineType routineType;

        Routine(std::string _sensorName, std::string _status, QDateTime _dateTime, RoutineType _routineType) {
            sensorName = _sensorName;
            status = _status;
            dateTime = _dateTime;
            routineType = _routineType;
        }
    };

    class RoutineThread : public QThread
    {
        Q_OBJECT
    private:
        bool status = true;
        QReadWriteLock lock;
        std::vector<Routine> routines;

        void run() {
            while (status) {
                QTime dieTime = QTime::currentTime().addMSecs(1000);

                {
                    QWriteLocker locker(&lock);

                    for (auto &r : routines) {
                        switch (r.routineType) {
                            case NoRepeat:
                                if (r.dateTime <= QDateTime::currentDateTime()) {
                                    if (!r.checked) {
                                        int statusRequest;
                                        std::string requestMessage;
                                        APIAccessPoint::instance().setSensorStatus(r.sensorName, r.status, requestMessage, statusRequest);

                                        r.checked = true;
                                    }
                                }

                                break;

                            case Daily:
                                break;

                            case Weekly:

                                break;
                            case Monthly:

                                break;

                            default:
                                break;
                        }
                    }
                }

                while (QTime::currentTime() < dieTime && status)
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            }
        }

    public:
        RoutineThread ()
        {
        }

        ~RoutineThread() {

        }

        void setMessage(const QString &_message) {}

        void stop() {
            status = false;
        }

        void addRountine(std::string sensorName, std::string status, QDateTime dateTime, RoutineType _routineType) {
            QWriteLocker locker(&lock);

            routines.push_back(Routine(sensorName, status, dateTime, _routineType));
        }

        std::vector<Routine> getRoutines() {
            return routines;
        }
    };


    class RoutineAccessPoint {
    private:
        std::unique_ptr<RoutineThread> rountineThread;

        RoutineAccessPoint() {
            std::ifstream routineFile;
            routineFile.open(ROUNTINES_FILE);

            rountineThread.reset(new RoutineThread());

            if (routineFile.good()) {
                std::string routineType;
                std::string sensorName, status;
                std::string day, month, year, hour, minute, second;

                while (!routineFile.eof()) {
                    getline(routineFile, sensorName);
                    if (routineFile.eof()) break;
                    getline(routineFile, status);
                    if (routineFile.eof()) break;
                    getline(routineFile, day);
                    if (routineFile.eof()) break;
                    getline(routineFile, month);
                    if (routineFile.eof()) break;
                    getline(routineFile, year);
                    if (routineFile.eof()) break;
                    getline(routineFile, second);
                    if (routineFile.eof()) break;
                    getline(routineFile, minute);
                    if (routineFile.eof()) break;
                    getline(routineFile, hour);
                    if (routineFile.eof()) break;
                    getline(routineFile, routineType);

                    QDate date(atoi(year.c_str()), atoi(month.c_str()), atoi(day.c_str()));
                    QTime time(atoi(hour.c_str()), atoi(minute.c_str()), atoi(second.c_str()));
                    QDateTime dateTime = QDateTime(date, time);

//                    printf("Sensor: %s -- %s (%s %s %s  -- %s %s %s)\n", sensorName.c_str(), status.c_str(), year.c_str(), month.c_str(), day.c_str(), hour.c_str(), minute.c_str(), second.c_str());

                    if (atoi(routineType.c_str()) == NoRepeat) {
                        if (dateTime > QDateTime::currentDateTime()) {
                            rountineThread->addRountine(sensorName, status, dateTime, RoutineType(atoi(routineType.c_str())));
                        }
                    } else {
                        rountineThread->addRountine(sensorName, status, dateTime, RoutineType(atoi(routineType.c_str())));
                    }
                }
            }

            rountineThread->start();
        }

        ~RoutineAccessPoint() {
            try {
                if (rountineThread) {
                    rountineThread->stop();

                    while (rountineThread->isRunning());

                    rountineThread.release();
                }
            } catch (std::exception& e) { }
        }

    public:
        RoutineAccessPoint(RoutineAccessPoint&&) = delete;
        RoutineAccessPoint(const RoutineAccessPoint&) = delete;
        RoutineAccessPoint& operator=(const RoutineAccessPoint&) = delete;
        RoutineAccessPoint& operator=(RoutineAccessPoint&&) = delete;

        static RoutineAccessPoint& instance() {
            static RoutineAccessPoint INSTANCE;
            return INSTANCE;
        }

        void addRountine(std::string sensorName, std::string status, QDateTime dateTime, RoutineType _routineType) {
            rountineThread->addRountine(sensorName, status, dateTime, _routineType);

            std::ofstream out;
            out.open(ROUNTINES_FILE, std::ios::app);

            if (out.good()) {
                out << sensorName << "\n"
                    << status << "\n"
                    << std::to_string(dateTime.date().day()) << "\n"
                    << std::to_string(dateTime.date().month()) << "\n"
                    << std::to_string(dateTime.date().year()) << "\n"
                    << std::to_string(dateTime.time().second()) << "\n"
                    << std::to_string(dateTime.time().minute()) << "\n"
                    << std::to_string(dateTime.time().hour()) << "\n"
                    << std::to_string(char(_routineType)) << "\n";

                out.close();
            }
        }

        void start() {}

        std::vector<Routine> getRoutines() {
            return rountineThread->getRoutines();
        }
    };
}

#endif // ROUTINETHREAD_H
