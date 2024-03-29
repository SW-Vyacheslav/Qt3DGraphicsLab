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
    ~MainWindow() override;

private:
    Thorus& getThorus();
    void updateTransformWidgets();
    void closeEvent(QCloseEvent *event) override;

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
    void ambientLightValueChanged(int val);
    void diffuseLightValueChanged(int val);
    void specularLightValueChanged(int val);

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
    Vector3DWidget* m_lightWidg;
};

#endif // MAINWINDOW_H
