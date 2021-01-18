#ifndef HISTORYDATA_H
#define HISTORYDATA_H

#include <vector>
#include <string>
#include <Util.h>
#include <QDateTime>

class HistoryData {
  private:
    std::string day_;
    std::string month_;
    std::string year_;
    std::string hour_;
    std::string minute_;
    std::string second_;
    std::string value_;

  public:
    std::string day() {return day_;}
    std::string month() {return month_;}
    std::string year() {return year_;}
    std::string hour() {return hour_;}
    std::string minute() {return minute_;}
    std::string second() {return second_;}
    std::string value() {return value_;}

    HistoryData() {}

    HistoryData(std::string rawData) {
        std::vector<std::string> elements = util::split(rawData, "-");

        year_ = elements[0];
        month_ = elements[1];
        day_ = elements[2];
        hour_ = elements[3];
        minute_ = elements[4];
        second_ = elements[5];
        value_ = elements[6];
    }

    QDateTime toQDateTime() const {
        return QDateTime(QDate(atoi(year_.c_str()), atoi(month_.c_str()), atoi(day_.c_str())),
                         QTime(atoi(hour_.c_str()), atoi(minute_.c_str()), atoi(second_.c_str()), 0));
    }
};

#endif // HISTORYDATA_H
