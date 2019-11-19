#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgets/worldwidget.h"
#include "widgets/vector3dwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void vc(int a);

private:
    Ui::MainWindow *ui;
    WorldWidget* m_worldWidget;
    Vector3DWidget* m_opPosWidg;
    Vector3DWidget* m_translateWidg;
    Vector3DWidget* m_rotateWidg;
    Vector3DWidget* m_scaleWidg;
};

#endif // MAINWINDOW_H
