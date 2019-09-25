#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPainter"
#include "graphics/thorus.h"
#include "graphics/projection.h"
#include "QPointF"

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
    bool eventFilter(QObject* watched, QEvent* event);
    void drawObject(QPainter& painter);
    QList<QPointF> PointsToCoordSystem(const QList<QPointF>& vertices);

public slots:
    void generateObject();
    void translateObject();
    void scaleObject();
    void rotateObject();

private:
    Ui::MainWindow *ui;
    bool m_isUpdate;
    Thorus m_thorus;
    Vector3D m_coordSysCenter;
    Projection* m_projection;
};

#endif // MAINWINDOW_H
