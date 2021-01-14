#ifndef GETSENSORSDIALOG_H
#define GETSENSORSDIALOG_H

#include <QDialog>

#include <QCheckBox>
#include <QComboBox>
#include <apiaccesspoint.h>

#include <SmartDevice.h>

namespace Ui {
class GetSensorsDialog;
}

class GetSensorsDialog : public QDialog
{
    Q_OBJECT

public:
    std::vector<SmartDevice> selectedSensors;

    explicit GetSensorsDialog(QWidget *parent = nullptr, std::vector<std::string> _sensors = std::vector<std::string>(), float _x = 0, float _y = 0);
    ~GetSensorsDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    float x, y;
    Ui::GetSensorsDialog *ui;


    std::vector<std::pair<QCheckBox *, QComboBox *>> sensorsWidgets;
};

#endif // GETSENSORSDIALOG_H
