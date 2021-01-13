#ifndef SENSORINFODIALOG_H
#define SENSORINFODIALOG_H

#include <QDialog>

namespace Ui {
class SensorInfoDialog;
}

class SensorInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorInfoDialog(QWidget *parent = nullptr);
    ~SensorInfoDialog();

private:
    Ui::SensorInfoDialog *ui;
};

#endif // SENSORINFODIALOG_H
