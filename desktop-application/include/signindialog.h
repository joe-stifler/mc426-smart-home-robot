#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <string>
#include <QDialog>

namespace Ui {
class SignInDialog;
}

class SignInDialog : public QDialog
{
    Q_OBJECT

public:
    std::string name;
    std::string email;
    std::string password;

    explicit SignInDialog(QWidget *parent = nullptr, std::string name = "", std::string email = "", std::string password = "");
    ~SignInDialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::SignInDialog *ui;
};

#endif // SIGNINDIALOG_H
