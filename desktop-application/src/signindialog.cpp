#include "signindialog.h"
#include "ui_signindialog.h"

SignInDialog::SignInDialog(QWidget *parent, std::string name, std::string email, std::string password) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);

    ui->edit_name->setText(QString::fromStdString(name));

    ui->edit_email->setText(QString::fromStdString(email));

    ui->edit_password->setText(QString::fromStdString(password));

    setWindowTitle("Sign-Up Dialog");
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::on_pushButton_2_clicked()
{
    name = ui->edit_name->text().toStdString();
    email = ui->edit_email->text().toStdString();
    password = ui->edit_password->text().toStdString();

    done(1);
}
