#include "profileprojection.h"

ProfileProjection::ProfileProjection() {}

ProfileProjection::~ProfileProjection() {}

QList<Point> ProfileProjection::GetProjectionPoints(const QList<Vertex> &vertices)
{
    QList<Point> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Point point;
        point.x = vertices[i].GetPosition().GetY();
        point.y = vertices[i].GetPosition().GetZ();
        val.push_back(point);
    }
    return val;
}
