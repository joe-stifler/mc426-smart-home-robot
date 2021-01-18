#include "getsensorsdialog.h"
#include "ui_getsensorsdialog.h"

#include <QMessageBox>

QComboBox *getComboBoxSensor() {
    QComboBox *comboBox = new QComboBox();

    comboBox->addItem("Luz");
    comboBox->addItem("Energia");
    comboBox->addItem("Ar Condicionado");
    comboBox->addItem("Camera");
    comboBox->addItem("Presença");
    comboBox->addItem("Temperatura");

    return comboBox;
}

std::vector<SmartDevice> GetSensorsDialog::getSelectedDevices()
{
    return selectedSensors;
}

GetSensorsDialog::GetSensorsDialog(QWidget *parent, std::vector<std::string> _sensors, float _x, float _y) :
    QDialog(parent),
    ui(new Ui::GetSensorsDialog)
{
    x = _x;
    y = _y;

    ui->setupUi(this);

    for (auto &s : _sensors) {
        QComboBox *comboBox = getComboBoxSensor();
        QCheckBox *checkBox = new QCheckBox(s.c_str());

        ui->vLayout_cbs->addWidget(checkBox);
        ui->vLayout_types->addWidget(comboBox);

        sensorsWidgets.push_back(std::make_pair(checkBox, comboBox));
    }

    setWindowTitle("Sensors Available Dialog");
}

GetSensorsDialog::~GetSensorsDialog()
{
    delete ui;

    for (auto &p : sensorsWidgets) {
        delete p.first;
        delete p.second;
    }
}

void GetSensorsDialog::on_pushButton_2_clicked()
{
    for (auto &p : sensorsWidgets) {
        if (p.first->isChecked()) {
            switch (p.second->currentIndex()) {
                case 0:
                    selectedSensors.push_back(SmartDeviceFactory::instance().getSmartDevice(x, y, SmartLamp, p.first->text().toStdString()));
                    break;
                case 1:
                    selectedSensors.push_back(SmartDeviceFactory::instance().getSmartDevice(x, y, SmartEnergy, p.first->text().toStdString()));
                    break;
                case 2:
                    selectedSensors.push_back(SmartDeviceFactory::instance().getSmartDevice(x, y, SmartAir, p.first->text().toStdString()));
                    break;
                case 3:
                    selectedSensors.push_back(SmartDeviceFactory::instance().getSmartDevice(x, y, SmartCamera, p.first->text().toStdString()));
                    break;
                case 4:
                    selectedSensors.push_back(SmartDeviceFactory::instance().getSmartDevice(x, y, SmartPresence, p.first->text().toStdString()));
                    break;
                case 5:
                    selectedSensors.push_back(SmartDeviceFactory::instance().getSmartDevice(x, y, SmartTemperature, p.first->text().toStdString()));
                    break;
            }
        }
    }

    done(1);
}

void GetSensorsDialog::on_pushButton_clicked()
{
    done(0);
}
