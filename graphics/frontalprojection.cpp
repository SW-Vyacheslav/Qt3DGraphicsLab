#include "frontalprojection.h"
#include "vertex.h"

FrontalProjection::FrontalProjection() {}

FrontalProjection::~FrontalProjection() {}

QList<Point> FrontalProjection::GetProjectionPoints(const QList<Vertex>& vertices)
{
    QList<Point> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Point point;
        point.x = vertices[i].GetPosition().GetX();
        point.y = vertices[i].GetPosition().GetY();
        val.push_back(point);
    }
    return val;
}
