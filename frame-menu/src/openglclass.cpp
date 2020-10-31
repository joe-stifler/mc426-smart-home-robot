#include "openglclass.h"

#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImageWriter>
#include <QMessageBox>
#include <QPainter>
#include <QScreen>
#include <QStandardPaths>
#include <QTimer>

#include <unistd.h>
#include <stdio.h>

OpenGLClass::OpenGLClass(QWidget *parent) : QOpenGLWidget (parent) {
    setlocale(LC_ALL, "C");

    QOpenGLWidget::makeCurrent();

    this->setMouseTracking(true);
    this->installEventFilter(this);

    QSurfaceFormat format;
    format.setDepthBufferSize( 4 );
    format.setSamples(4);
    format.setVersion(3, 3);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile( QSurfaceFormat::CoreProfile );

    QSurfaceFormat::setDefaultFormat(format);

    this->setFormat( format );

    QScreen *_screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = _screen->geometry();

    maximumWidth = screenGeometry.width();
    maximumHeight = screenGeometry.height();
}

OpenGLClass::~OpenGLClass() {
    QOpenGLWidget::makeCurrent();

    if (vbo.get() != nullptr) vbo->destroy();
    if (vao.get() != nullptr) vao->destroy();
    if (texturePlot != nullptr) texturePlot->destroy();
    if (myShader.get() != nullptr) myShader->deleteLater();
}

void OpenGLClass::updateTexture(uchar *data) {
    QOpenGLWidget::makeCurrent();

    // Disable byte-alignment restriction
    this->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    texturePlot->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<const void*>(data));
    update();
}

void OpenGLClass::setNewTexture(int _texturePlotWidth, int _texturePlotHeight) {
    QOpenGLWidget::makeCurrent();

    if(texturePlot)
        texturePlot->destroy();

    /* Configure the texture object */
    texturePlot = std::unique_ptr<QOpenGLTexture>(new QOpenGLTexture(QOpenGLTexture::Target2D));
    texturePlot->create();

    texturePlot->setMagnificationFilter(QOpenGLTexture::Linear);
    texturePlot->setMinificationFilter(QOpenGLTexture::Linear);
    texturePlot->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
    texturePlot->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);

    // Disable byte-alignment restriction
    this->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    texturePlot->setFormat(QOpenGLTexture::R8_UNorm);
    texturePlot->setSize(static_cast<int>(_texturePlotWidth), static_cast<int>(_texturePlotHeight), 1);
    texturePlot->allocateStorage(QOpenGLTexture::Red, QOpenGLTexture::UInt8);
}

void OpenGLClass::initializeGL() {
    this->initializeOpenGLFunctions();
    QOpenGLWidget::makeCurrent();

    /* prevents wrong supperposition of pixels */
    this->glEnable(GL_DEPTH_TEST);

    /* Useful for the text texture */
    this->glEnable(GL_BLEND);
    this->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Configure the shader program */
    myShader.reset(new QOpenGLShaderProgram);
    myShader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex.vert");
    myShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment.frag");
    myShader->link();
    myShader->bind();

    QMatrix4x4 projection;
    projection.ortho(0.0f, static_cast<GLfloat>(maximumWidth), 0.0f, static_cast<GLfloat>(maximumHeight), 0.1f, 1.0f);
    myShader->setUniformValue("projection", projection);

    const float margins[4] = {
        0.04f, /* left */
        0.04f, /* right */
        0.06f, /* up */
        0.04f  /* down */
    };

    std::unique_ptr<point> vertices(new point[nDefaultPts]);

    /* Up central triangle */
    vertices.get()[0] = {-1.0f + margins[0], 1.0f - margins[2], 0.0f, 0.0f};
    vertices.get()[1] = { 1.0f - margins[1], 1.0f - margins[2], 1.0f, 0.0f};
    vertices.get()[2] = { 1.0f - margins[1], -1.0f + margins[3], 1.0f, 1.0f};

    /* Down central triangle */
    vertices.get()[3] = { 1.0f - margins[1], -1.0f + margins[3], 1.0f, 1.0f};
    vertices.get()[4] = {-1.0f + margins[0], -1.0f + margins[3], 0.0f, 1.0f};
    vertices.get()[5] = {-1.0f + margins[0], 1.0f - margins[2], 0.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[6] = {-1.0f, 1.0f, -2.0f, 0.0f};
    vertices.get()[7] = {-1.0f + margins[0], 1.0f, -2.0f, 0.0f};
    vertices.get()[8] = {-1.0f + margins[0], -1.0f, -2.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[9] = {-1.0f, 1.0f, -2.0f, 0.0f};
    vertices.get()[10] = {-1.0f, -1.0f, -2.0f, 0.0f};
    vertices.get()[11] = {-1.0f + margins[0], -1.0f, -2.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[12] = {1.0f, 1.0f, -2.0f, 0.0f};
    vertices.get()[13] = {1.0f, -1.0f, -2.0f, 0.0f};
    vertices.get()[14] = {1.0f - margins[1], -1.0f, -2.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[15] = {1.0f, 1.0f, -2.0f, 0.0f};
    vertices.get()[16] = {1.0f - margins[1], 1.0f, -2.0f, 0.0f};
    vertices.get()[17] = {1.0f - margins[1], -1.0f, -2.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[18] = {-1.0f, 1.0f, -2.0f, 0.0f};
    vertices.get()[19] = {1.0f, 1.0f, -2.0f, 0.0f};
    vertices.get()[20] = {1.0f, 1.0f - margins[2], -2.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[21] = {1.0f, 1.0f - margins[2], -2.0f, 0.0f};
    vertices.get()[22] = {-1.0f, 1.0f - margins[2], -2.0f, 0.0f};
    vertices.get()[23] = {-1.0f, 1.0f, -2.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[24] = {-1.0f, -1.0f, -2.0f, 0.0f};
    vertices.get()[25] = {-1.0f, -1.0f + margins[3], -2.0f, 0.0f};
    vertices.get()[26] = {1.0f, -1.0f + margins[3], -2.0f, 0.0f};

    /* Lateral triangle */
    vertices.get()[27] = {-1.0f, -1.0f, -2.0f, 0.0f};
    vertices.get()[28] = {1.0f, -1.0f, -2.0f, 0.0f};
    vertices.get()[29] = {1.0f, -1.0f + margins[3], -2.0f, 0.0f};

    /* Box */
    vertices.get()[30] = {-1.0f + margins[0], 1.0f - margins[2], -1.0f, 0.0f};
    vertices.get()[31] = { 1.0f - margins[1], 1.0f - margins[2], -1.0f, 0.0f};
    vertices.get()[32] = { 1.0f - margins[1], -1.0f + margins[3], -1.0f, 0.0f};
    vertices.get()[33] = {-1.0f + margins[0], -1.0f + margins[3], -1.0f, 0.0f};

    /* Configures the vertex object array */
    vao = std::unique_ptr<QOpenGLVertexArrayObject>(new QOpenGLVertexArrayObject());
    vao->create();
    vao->bind();

    /* Configures the vertex buffer object */
    vbo.reset(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
    vbo->create();
    vbo->setUsagePattern( QOpenGLBuffer::StaticDraw );
    vbo->bind();
    vbo->allocate(vertices.get(), (nDefaultPts) * static_cast<int>(sizeof(point)));

    myShader->enableAttributeArray("vertex");
    myShader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 4 * sizeof(float));
}

void OpenGLClass::resizeGL(int width, int height) {
    QOpenGLWidget::makeCurrent();

    this->glViewport(0, 0, width, height);
}

void OpenGLClass::paintGL() {
    QOpenGLWidget::makeCurrent();

    this->glClearColor(1.0, 1.0, 1.0, 1.0);
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao->bind();
    vbo->bind();
    myShader->bind();

    if (texturePlot) {
        texturePlot->bind();

        transform = QMatrix4x4();

        transform.scale(1.0f, 1.0f, 1);

        transform.translate(0.0f, 0.0f, 0);

        myShader->setUniformValue("transform", transform);

        myShader->setUniformValue("stage", 0);

        this->glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    myShader->setUniformValue("stage", 1);
    this->glDrawArrays(GL_TRIANGLES, 6, nDefaultPts - 10);

    myShader->setUniformValue("stage", 2);
    this->glDrawArrays(GL_LINE_LOOP, nDefaultPts - 4, 4);
}
