#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>
#include "graphics/components/worldobject.h"
#include "graphics/components/camera.h"
#include "graphics/components/vertex.h"
#include "graphics/projections/projection.h"
#include "graphics/components/zbuffer.h"
#include "math/Vector2D.h"

class WorldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorldWidget(QWidget *parent = nullptr);

    enum DrawModel
    {
        WIREFRAME,
        SURFACE
    };

    WorldObject& GetWorldObject();
    void SetProjection(Projection* projection);

public slots:
    void SetDrawModel(const DrawModel& drawModel);

private:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QList<Vertex> VerticesToCoordSystem(const QList<Vertex>& vertices);
    void fillTriangle(Vertex v1, Vertex v2, Vertex v3, const QRgb& color);
    void swapVerts(Vertex& v1, Vertex& v2);

    void drawObjectSurface();
    void drawObjectWireframe();
    void drawMisc();

    QList<Vertex> transformVertices(const QList<Vertex>& vertices);
    void recalculateNormals(const QList<Vertex>& vertices);

private:
    WorldObject* m_worldObject;
    Projection* m_projection;
    ZBuffer* m_zBuffer;
    Vector2D m_coordSysCenter;
    DrawModel m_drawModel;
};

#endif // WORLDWIDGET_H
