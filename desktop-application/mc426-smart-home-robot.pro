QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 -w

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -w -O3

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/apiaccesspoint.cpp \
    src/apirequest.cpp \
    src/getsensorsdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/openglclass.cpp \
    src/signindialog.cpp

HEADERS += \
    include/HTTPRequest.h \
    include/SmartDevice.h \
    include/Util.h \
    include/mainwindow.h \
    include/openglclass.h \
    include/apiaccesspoint.h \
    include/getsensorsdialog.h \
    include/apirequest.h \
    include/signindialog.h

FORMS += \
    forms/mainwindow.ui \
    forms/getsensorsdialog.ui \
    forms/signindialog.ui

INCLUDEPATH += include/

DISTFILES += \
    shaders/* \
    images/*

#Output
UI_DIR      = uic
MOC_DIR     = moc
OBJECTS_DIR = obj

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
