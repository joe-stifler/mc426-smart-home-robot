#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <QDialog>

namespace Ui {
class SignInDialog;
}

class SignInDialog : public QDialog
{
    Q_OBJECT

public:
    std::string getEmail();
    std::string getPassword();

    explicit SignInDialog(QWidget *parent = nullptr, std::string email = "5", std::string password = "");
    ~SignInDialog();

private slots:
    void on_pushButton_clicked();

private:
    std::string email;
    std::string password;
    Ui::SignInDialog *ui;
};

#endif // SIGNINDIALOG_H
