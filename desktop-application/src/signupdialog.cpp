#include "signupdialog.h"
#include "ui_signupdialog.h"

SignUpDialog::SignUpDialog(QWidget *parent, std::string _name, std::string _email, std::string _password) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);

    ui->edit_name->setText(QString::fromStdString(_name));

    ui->edit_email->setText(QString::fromStdString(_email));

    ui->edit_password->setText(QString::fromStdString(_password));

    setWindowTitle("Sign-Up Dialog");
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_pushButton_2_clicked()
{
    name = ui->edit_name->text().toStdString();
    email = ui->edit_email->text().toStdString();
    password = ui->edit_password->text().toStdString();

    done(1);
}
