#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    uchar *imageData;
    std::unique_ptr<uchar> imageData2;
    std::unique_ptr<float> imageDataAux;

    int height, width, nrChannels;

    void plotData();
};
#endif // MAINWINDOW_H
