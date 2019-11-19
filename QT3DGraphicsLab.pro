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
    graphics/components/camera.cpp \
    graphics/components/transformmatrixcreator.cpp \
    graphics/components/worldobject.cpp \
    mainwindow.cpp \
    graphics/components/mesh.cpp \
    graphics/components/transform.cpp \
    graphics/components/vertex.cpp \
    graphics/projections/axonometricprojection.cpp \
    graphics/projections/frontalprojection.cpp \
    graphics/projections/horizontalprojection.cpp \
    graphics/projections/obliqueprojection.cpp \
    graphics/projections/perspectiveprojection.cpp \
    graphics/projections/profileprojection.cpp \
    graphics/projections/projection.cpp \
    graphics/thorus.cpp \
    math/Converter.cpp \
    math/Matrix4x4.cpp \
    math/Vector2D.cpp \
    math/Vector3D.cpp \
    widgets/transformwidget.cpp \
    widgets/vector3dwidget.cpp \
    widgets/worldwidget.cpp

HEADERS  += mainwindow.h \
    graphics/components/camera.h \
    graphics/components/edge.h \
    graphics/components/face.h \
    graphics/components/mesh.h \
    graphics/components/transform.h \
    graphics/components/transformmatrixcreator.h \
    graphics/components/vertex.h \
    graphics/components/worldobject.h \
    graphics/projections/axonometricprojection.h \
    graphics/projections/frontalprojection.h \
    graphics/projections/horizontalprojection.h \
    graphics/projections/obliqueprojection.h \
    graphics/projections/perspectiveprojection.h \
    graphics/projections/profileprojection.h \
    graphics/projections/projection.h \
    graphics/thorus.h \
    graphics/projections.h \
    math/Converter.h \
    math/Matrix4x4.h \
    math/Vector2D.h \
    math/Vector3D.h \
    widgets/transformwidget.h \
    widgets/vector3dwidget.h \
    widgets/worldwidget.h

FORMS    += mainwindow.ui
