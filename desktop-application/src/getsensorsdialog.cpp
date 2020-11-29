#include "getsensorsdialog.h"
#include "ui_getsensorsdialog.h"

QComboBox *getComboBoxSensor() {
    QComboBox *comboBox = new QComboBox();

    comboBox->addItem("Luz");
    comboBox->addItem("Energia");
    comboBox->addItem("Agua");
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

    std::cout << "SENSOR AVAILABLE" << std::endl;
    auto sensors = APIAccessPoint::instance().sensorAvailable(requestMessage, status);

    std::cout << "Status: " << status << std::endl;
    std::cout << "request message: " << requestMessage << std::endl;

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
}

void GetSensorsDialog::on_pushButton_2_clicked()
{
    printf("Clicked Ok");
    fflush(stdout);
}

void GetSensorsDialog::on_pushButton_clicked()
{
    printf("Clicked Cancel");
    fflush(stdout);
}
