#ifndef GETSENSORSDIALOG_H
#define GETSENSORSDIALOG_H

#include <QDialog>

#include <QCheckBox>
#include <QComboBox>
#include <apiaccesspoint.h>

namespace Ui {
class GetSensorsDialog;
}

class GetSensorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetSensorsDialog(QWidget *parent = nullptr);
    ~GetSensorsDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::GetSensorsDialog *ui;

    std::vector<std::pair<QCheckBox *, QComboBox *>> sensorsWidgets;
};

#endif // GETSENSORSDIALOG_H
