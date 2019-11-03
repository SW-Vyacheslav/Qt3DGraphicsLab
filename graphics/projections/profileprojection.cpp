#include "graphics/projections/profileprojection.h"

ProfileProjection::ProfileProjection() {}

ProfileProjection::~ProfileProjection() {}

QList<Point> ProfileProjection::GetProjectionPoints(const QList<Vertex> &vertices)
{
    QList<Point> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Point point;
        point.x = vertices[i].GetPosition().GetZ();
        point.y = vertices[i].GetPosition().GetY();
        val.push_back(point);
    }
    return val;
}
