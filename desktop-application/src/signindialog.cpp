#include "signindialog.h"
#include "ui_signindialog.h"

std::string SignInDialog::getEmail()
{
    return email;
}

std::string SignInDialog::getPassword()
{
    return password;
}

SignInDialog::SignInDialog(QWidget *parent, std::string _email, std::string _password) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);

    ui->edit_email->setText(QString::fromStdString(_email));

    ui->edit_password->setText(QString::fromStdString(_password));

    setWindowTitle("Sign-In Dialog");
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::on_pushButton_clicked()
{
    email = ui->edit_email->text().toStdString();
    password = ui->edit_password->text().toStdString();

    done(1);
}
