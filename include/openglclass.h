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


const char text_vert [] =
"#version 330\n"
"\n"
"in vec4 position;\n"
"out vec2 texCoords;\n"
"\n"
"void main(void) {\n"
"    gl_Position = vec4(position.xy, 0, 1);\n"
"    texCoords = position.zw;\n"
"}\n"
;

//#define FRAGMENT_CODE \
//"#version 330 core\n" \
//"\n" \
//"in vec2 textCoord;\n" \
//"out vec4 color;\n" \
//"uniform int stage;\n" \
//"uniform sampler2D text2d;\n" \
//"uniform vec3 textColor;\n" \
//"\n" \
//"vec4 jet(float t) {\n" \
//"return vec4(clamp(vec3(1.5) - abs(4.0 * vec3(t) + vec3(-3, -2, -1)), vec3(0), vec3(1)), 1.0);\n" \
//"}\n" \
//"\n" \
//"void main(void)\n" \
//"{\n" \
//"if (stage == 0) { /* Plots the plot */\n" \
//"float r = texture(text2d, textCoord).r;\n" \
//"color = vec4(r, r, r, 1.0f);\n" \
//"} else if (stage == 1) { /* Plots the lateral triangles */\n" \
//"float val = 240.0 / 255.0;\n" \
//"color = vec4(val, val, val, 1.0f);\n" \
//"} else if (stage == 2) { /* Plots the box and the ticks */\n" \
//"color = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n" \
//"}\n" \
//"}\n"

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
