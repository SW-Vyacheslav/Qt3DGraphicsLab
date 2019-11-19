#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>
#include "graphics/components/worldobject.h"
#include "graphics/components/camera.h"
#include "graphics/components/vertex.h"
#include "graphics/projections/projection.h"
#include "math/Vector2D.h"

class WorldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorldWidget(QWidget *parent = nullptr);

    WorldObject& GetWorldObject();

private:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void drawObject(QPainter& painter);
    QList<Vertex> VerticesToCoordSystem(const QList<Vertex>& vertices);

private:
    WorldObject* m_worldObject;
    Projection* m_projection;
    Vector2D m_coordSysCenter;
};

#endif // WORLDWIDGET_H
