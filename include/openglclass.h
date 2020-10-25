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

    void updateTexture(uchar *data);

    void setNewTexture(int _texturePlotWidth, int _texturePlotHeight);

protected:

    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int width, int height) override;

private:
    int maximumWidth;
    int maximumHeight;
    int nDefaultPts = 34;

    QMatrix4x4 transform;
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<QOpenGLBuffer> vbo;
    std::unique_ptr<uchar> textureData;
    std::unique_ptr<QOpenGLTexture> texturePlot;
    std::unique_ptr<QOpenGLVertexArrayObject> vao;
    std::unique_ptr<QOpenGLShaderProgram> myShader;
};

#endif // OPENGLCLASS_H
