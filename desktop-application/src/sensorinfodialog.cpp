#include "sensorinfodialog.h"
#include "ui_sensorinfodialog.h"

SensorInfoDialog::SensorInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorInfoDialog)
{
    ui->setupUi(this);
}

SensorInfoDialog::~SensorInfoDialog()
{
    delete ui;
}
