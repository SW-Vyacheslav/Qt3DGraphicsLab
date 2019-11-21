#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgets/worldwidget.h"
#include "widgets/vector3dwidget.h"
#include "graphics/thorus.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Thorus& getThorus();
    void updateTransformWidgets();

public slots:
    void generateObject();
    void translateObject();
    void scaleObject();
    void rotateObject();
    void setHorizontalProjection();
    void setFrontalProjection();
    void setProfileProjection();
    void setAxonometricProjection();
    void setObliqueProjection();
    void setPerspectiveProjection();
    void drawModelChanged();

private:
    Ui::MainWindow *ui;
    WorldWidget* m_worldWidget;
    Vector3DWidget* m_opPosWidg;
    Vector3DWidget* m_translateWidg;
    Vector3DWidget* m_rotateWidg;
    Vector3DWidget* m_scaleWidg;
    Vector3DWidget* m_transfPosWidg;
    Vector3DWidget* m_transfRotWidg;
    Vector3DWidget* m_transfScaleWidg;
};

#endif // MAINWINDOW_H
