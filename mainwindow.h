#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "graphics/renderobject.h"
#include "graphics/projection.h"
#include "graphics/point.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool eventFilter(QObject* object, QEvent* event);
    void drawObject(QPainter& painter);
    QList<Point> PointsToCoordSystem(const QList<Point>& vertices);

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
    void setOperationPoint();

private:
    Ui::MainWindow *ui;
    RenderObject* m_renderObject;
    Vector3D m_coordSysCenter;
    Vector3D m_operationPoint;
    Projection* m_projection;
};

#endif // MAINWINDOW_H
