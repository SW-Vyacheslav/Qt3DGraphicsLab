#include "graphics/projections/horizontalprojection.h"

HorizontalProjection::HorizontalProjection() {}

HorizontalProjection::~HorizontalProjection() {}

QList<Point> HorizontalProjection::GetProjectionPoints(const QList<Vertex>& vertices)
{
    QList<Point> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Point point;
        point.x = vertices[i].GetPosition().GetX();
        point.y = vertices[i].GetPosition().GetZ();
        val.push_back(point);
    }
    return val;
}
