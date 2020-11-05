#include <mainwindow.h>
#include "ui_mainwindow.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setlocale(LC_ALL, "C");

    ui->setupUi(this);

    setWindowTitle("Smart House Robot");

    showMaximized();

    plotData();
}

MainWindow::~MainWindow()
{
    delete ui;

    if (imageData) stbi_image_free(imageData);
}

void MainWindow::plotData() {
    imageData = stbi_load("images/floorplan.png", &width, &height, &nrChannels, 0);

    imageDataAux.reset(new float[width * height]);
    imageData2.reset(new uchar[3 * width * height]);

    float maxGrayScale = 0;

    for (int i = 0; i < width * height; ++i) {
        float R = (float) imageData[i * nrChannels + 0];
        float G = (float) imageData[i * nrChannels + 1];
        float B = (float) imageData[i * nrChannels + 2];

        float grayScale = 0.299 * R + 0.587 * G + 0.114 * B;

        maxGrayScale = std::max(maxGrayScale, grayScale);

        imageDataAux.get()[i] = grayScale;
    }

    for (int i = 0; i < width * height; ++i) {
        imageData2.get()[i] = (uchar) (imageDataAux.get()[i] / maxGrayScale * 255.0f);
    }

    ui->openGLWidget->setNewTexture(width, height);

    ui->openGLWidget->updateTexture(imageData2.get());
}

