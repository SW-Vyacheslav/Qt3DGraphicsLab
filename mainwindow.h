#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "graphics/components/worldobject.h"
#include "graphics/projections/projection.h"
#include "graphics/components/point.h"

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
    void setPerspectiveProjection();
    void setOperationPoint();
    void onObjectPositionChanged(const Vector3D& position);
    void updateWidgetOnChange();

private:
    Ui::MainWindow *ui;
    WorldObject* m_renderObject;
    Vector3D m_coordSysCenter;
    Vector3D m_operationPoint;
    Projection* m_projection;
};

#endif // MAINWINDOW_H
