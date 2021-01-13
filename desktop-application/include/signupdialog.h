#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <string>
#include <QDialog>

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    std::string name;
    std::string email;
    std::string password;

    explicit SignUpDialog(QWidget *parent = nullptr, std::string name = "", std::string email = "", std::string password = "");
    ~SignUpDialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::SignUpDialog *ui;
};

#endif // SIGNUPDIALOG_H
