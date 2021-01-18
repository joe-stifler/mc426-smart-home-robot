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

    if (vboDevice.get() != nullptr) vboDevice->destroy();
    if (vaoDevice.get() != nullptr) vaoDevice->destroy();

    if (texturePlot != nullptr) texturePlot->destroy();
    if (myShader.get() != nullptr) myShader->deleteLater();
}

QOpenGLTexture *createTexture(std::string imagePath) {
    QImage myImage;

    myImage.load(imagePath.c_str());

    if (!myImage.isNull()) {

        QOpenGLTexture *texture = new QOpenGLTexture(QOpenGLTexture::Target2D);

        texture->create();

        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setMinificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
        texture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);

        texture->setData(myImage);

        return texture;
    }

    return nullptr;
}

void OpenGLClass::setNewTexture(std::string imagePath) {
    QOpenGLWidget::makeCurrent();

    if(texturePlot) texturePlot->destroy();

    texturePlot.reset(createTexture(imagePath));

    update();
}

void OpenGLClass::addSmartDevice(SmartDevice *smartDevice) {
    if (smartDevice) {
        textureDevices.push_back(std::make_pair(smartDevice, std::unique_ptr<QOpenGLTexture>()));

        textureDevices[textureDevices.size() - 1].second.reset(createTexture(smartDevice->getPath()));

        update();
    }
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
    myShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/vertex.vert");
    myShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/fragment.frag");
    myShader->link();
    myShader->bind();

    QMatrix4x4 projection;
    projection.ortho(0.0f, static_cast<GLfloat>(maximumWidth), 0.0f, static_cast<GLfloat>(maximumHeight), 0.1f, 1.0f);
    myShader->setUniformValue("projection", projection);

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

    /* Configures the vertex object array */
    vaoDevice.reset(new QOpenGLVertexArrayObject());
    vaoDevice->create();
    vaoDevice->bind();

    /* Configures the vertex buffer object */
    vboDevice.reset(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
    vboDevice->create();
    vboDevice->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboDevice->bind();
    vboDevice->allocate(vertices.get(), 6 * static_cast<int>(sizeof(point)));

    myShader->enableAttributeArray("vertex");
    myShader->setAttributeBuffer("vertex", GL_FLOAT, 0, 4, 4 * sizeof(float));
}

void OpenGLClass::resizeGL(int width, int height) {
    QOpenGLWidget::makeCurrent();

    this->glViewport(0, 0, width, height);
}

void OpenGLClass::getNormalizedCoordinates(float x, float y, float &x_coord, float &y_coord) {
    float width = this->width();
    float height = this->height();

    float percentX = (margins[0]) / 2.0f;
    float percentY = (margins[2]) / 2.0f;

    float val_x = width * percentX;
    float val_y = height * percentY;

    fflush(stdout);
    x_coord = (x - val_x) / (width * (1.0f - (margins[0] + margins[1]) / 2.0f));
    y_coord = (y - val_y) / (height * (1.0f - (margins[2] + margins[3]) / 2.0f));
}

void OpenGLClass::getInverseNormalizedCoordinates(float x, float y, float &x_coord, float &y_coord) {
    float width = this->width();
    float height = this->height();

    float percentX = (margins[0]) / 2.0f;
    float percentY = (margins[2]) / 2.0f;

    float val_x = width * percentX;
    float val_y = height * percentY;

    x_coord = x * (width * (1.0f - (margins[0] + margins[1]) / 2.0f)) + val_x;
    y_coord = y * (height * (1.0f - (margins[2] + margins[3]) / 2.0f)) + val_y;
}

void OpenGLClass::mousePressEvent(QMouseEvent *event)
{
    QOpenGLWidget::makeCurrent();

    float x, y;

    pickedDevice = nullptr;

    getNormalizedCoordinates(event->x(), event->y(), x, y);

    if (x >= 0.0f && x <= 1.0f && y >= 0.0f && y <= 1.0f) {
        if (event->buttons() == Qt::LeftButton) {
            SmartDevice *pickedDevice2 = nullptr;

            for (auto &textureDevice : textureDevices) {
                if (textureDevice.second) {
                    auto smartDevice = textureDevice.first;

                    if (std::fabs(x - smartDevice->getX()) < smartDevice->getDx() / 2 && std::fabs(y - smartDevice->getY()) < smartDevice->getDy() / 2) {
                        pickedDevice2 = smartDevice;
                        break;
                    }
                }
            }

            if (pickedDevice2 == nullptr) emit ClickPlot(x, y);
            else emit ClickSensor(pickedDevice2);
        } else if (event->buttons() == Qt::RightButton) {
            for (auto &textureDevice : textureDevices) {
                if (textureDevice.second) {
                    auto smartDevice = textureDevice.first;

                    if (std::fabs(x - smartDevice->getX()) < smartDevice->getDx() / 2 && std::fabs(y - smartDevice->getY()) < smartDevice->getDy() / 2) {
                        pickedDevice = smartDevice;
                        break;
                    }
                }
            }
        }
    }
}

void OpenGLClass::mouseReleaseEvent(QMouseEvent *event)
{
    QOpenGLWidget::makeCurrent();

    float x_coord, y_coord;

    getNormalizedCoordinates(event->x(), event->y(), x_coord, y_coord);

    if (x_coord >= 0.0f && x_coord <= 1.0f && y_coord >= 0.0f && y_coord <= 1.0f) {
        if (event->button() == Qt::LeftButton) {

        } else if (event->button() == Qt::RightButton) {
            if (pickedDevice) {
                pickedDevice->setX(x_coord);
                pickedDevice->setY(y_coord);
                update();
            }
        }
    }

    pickedDevice = nullptr;
}

void OpenGLClass::mouseMoveEvent(QMouseEvent *event)
{
    QOpenGLWidget::makeCurrent();

    float x_coord, y_coord;

    getNormalizedCoordinates(event->x(), event->y(), x_coord, y_coord);

    if (x_coord >= 0.0f && x_coord <= 1.0f && y_coord >= 0.0f && y_coord <= 1.0f) {
        if (pickedDevice) {
            pickedDevice->setX(x_coord);
            pickedDevice->setY(y_coord);
            update();
        }
    }
}

void OpenGLClass::paintGL() {
    QOpenGLWidget::makeCurrent();

    this->glClearColor(1.0, 1.0, 1.0, 1.0);
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao->bind();
    vbo->bind();
    myShader->bind();

    transform = QMatrix4x4();

    transform.scale(1.0f, 1.0f, 1);

    transform.translate(0.0f, 0.0f, 0);

    myShader->setUniformValue("transform", transform);

    myShader->setUniformValue("stage", 1);
    this->glDrawArrays(GL_TRIANGLES, 6, nDefaultPts - 10);

    myShader->setUniformValue("stage", 2);
    this->glDrawArrays(GL_LINE_LOOP, nDefaultPts - 4, 4);

    /* plot the robot */
    float x_origin = 0.5;
    float z_origin = 0.5;

    float x, z;
    getInverseNormalizedCoordinates(x_origin, z_origin, x, z);

    x = 2.0f * x / (float) width() - 1.0f;
    z = 2.0f * (1.0f - z / (float) height()) - 1.0f;

    vboDevice->bind();

    vaoDevice->bind();

    myShader->setUniformValue("stage", 3);

    for (auto &textureDevice : textureDevices) {
        if (textureDevice.second) {
            textureDevice.second->bind();

            SmartDevice *smartDevice = textureDevice.first;

            if (smartDevice) {
                float dx = smartDevice->getDx();
                float dy = smartDevice->getDy();
                point vertices[6];

                float x, y;
                getInverseNormalizedCoordinates(smartDevice->getX(), smartDevice->getY(), x, y);

                x = 2.0f * x / (float) width() - 1.0f;
                y = 2.0f * (1.0f - y / (float) height()) - 1.0f;

                /* Up central triangle */
                vertices[0] = {x - dx, y + dy, 0.0f, 0.0f};
                vertices[1] = {x + dx, y + dy, 1.0f, 0.0f};
                vertices[2] = {x + dx, y - dy, 1.0f, 1.0f};

                /* Down central triangle */
                vertices[3] = {x + dx, y - dy, 1.0f, 1.0f};
                vertices[4] = {x - dx, y - dy, 0.0f, 1.0f};
                vertices[5] = {x - dx, y + dy, 0.0f, 0.0f};

                // Update content of VBO memory
                vboDevice->write(0, &vertices[0], 6 * sizeof(point));

                transform = QMatrix4x4();

                transform.scale(1.0f, 1.0f, 1);

                transform.translate(0.0f, 0.0f, 0);

                myShader->setUniformValue("transform", transform);

                myShader->setUniformValue("stage", 0);

                this->glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }
    }

    vao->bind();
    vbo->bind();

    if (texturePlot) {
        texturePlot->bind();

        transform = QMatrix4x4();

        transform.scale(1.0f, 1.0f, 1);

        transform.translate(0.0f, 0.0f, 0);

        myShader->setUniformValue("transform", transform);

        myShader->setUniformValue("stage", 0);

        this->glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
