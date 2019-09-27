#-------------------------------------------------
#
# Project created by QtCreator 2019-09-12T00:22:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT3DGraphicsLab
TEMPLATE = app

SOURCES += main.cpp \
    graphics/frontalprojection.cpp \
    graphics/horizontalprojection.cpp \
    graphics/profileprojection.cpp \
    graphics/projection.cpp \
    graphics/thorus.cpp \
    mainwindow.cpp \
    graphics/mesh.cpp \
    graphics/vertex.cpp \
    graphics/renderobject.cpp \
    math/Converter.cpp \
    math/Matrix4x4.cpp \
    math/Vector3D.cpp

HEADERS  += mainwindow.h \
    graphics/frontalprojection.h \
    graphics/horizontalprojection.h \
    graphics/mesh.h \
    graphics/point.h \
    graphics/profileprojection.h \
    graphics/projection.h \
    graphics/renderobject.h \
    graphics/thorus.h \
    graphics/vertex.h \
    math/Converter.h \
    math/Matrix4x4.h \
    math/Vector3D.h

FORMS    += mainwindow.ui
