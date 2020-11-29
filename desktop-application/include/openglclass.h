#ifndef OPENGLCLASS_H
#define OPENGLCLASS_H

#include <cmath>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <QMouseEvent>
#include <QEvent>
#include <QKeyEvent>

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>

#include <SmartDevice.h>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);

struct point {
    float x; /**< \brief X variable */
    float y; /**< \brief Y variable */
    float z; /**< \brief Z variable */
    float w; /**< \brief W variable */
};

class OpenGLClass : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    ~OpenGLClass() override;

    explicit OpenGLClass(QWidget *parent = nullptr);

    void setNewTexture(std::string imagePath);

    void addSmartDevice(SmartDevice *smartDevice);

signals:
    void ClickPlot(float x, float y);

protected:

    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height) override;

private:
    int maximumWidth;
    int maximumHeight;
    int nDefaultPts = 34;

    float margins[4] = {
        0.04f, /* left */
        0.04f, /* right */
        0.06f, /* up */
        0.04f  /* down */
    };

    SmartDevice *pickedDevice = nullptr;

    QMatrix4x4 transform;
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<QOpenGLBuffer> vbo;
    std::unique_ptr<QOpenGLTexture> texturePlot;
    std::unique_ptr<QOpenGLVertexArrayObject> vao;
    std::unique_ptr<QOpenGLShaderProgram> myShader;

    std::unique_ptr<QOpenGLBuffer> vboDevice;
    std::unique_ptr<QOpenGLVertexArrayObject> vaoDevice;
    std::vector<std::pair<SmartDevice *, std::unique_ptr<QOpenGLTexture>>> textureDevices;

    void getNormalizedCoordinates(float x, float y, float &x_coord, float &y_coord);
    void getInverseNormalizedCoordinates(float x, float y, float &x_coord, float &y_coord);

    void RenderRobot(GLfloat x, GLfloat y, GLfloat scale, QVector3D color, int orientation);

protected:
    // Declare that we are overriding QWidget's events for mouse press and release
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // OPENGLCLASS_H
