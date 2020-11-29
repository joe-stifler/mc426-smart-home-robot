#include "getsensorsdialog.h"
#include "ui_getsensorsdialog.h"

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

GetSensorsDialog::GetSensorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetSensorsDialog)
{
    ui->setupUi(this);

    int status;
    std::string requestMessage;

    auto sensors = APIAccessPoint::instance().sensorAvailable(requestMessage, status);

    for (auto &s : sensors) {
        QComboBox *comboBox = getComboBoxSensor();
        QCheckBox *checkBox = new QCheckBox(s.c_str());

        ui->vLayout_cbs->addWidget(checkBox);
        ui->vLayout_types->addWidget(comboBox);

        sensorsWidgets.push_back(std::make_pair(checkBox, comboBox));
    }
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
                    selectedSensors.push_back(SmartLamp);
                    break;
                case 1:
                    selectedSensors.push_back(SmartEnergy);
                    break;
                case 2:
                    selectedSensors.push_back(SmartAir);
                    break;
                case 3:
                    selectedSensors.push_back(SmartCamera);
                    break;
                case 4:
                    selectedSensors.push_back(SmartPresence);
                    break;
                case 5:
                    selectedSensors.push_back(SmartTemperature);
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
