#include "graphics/projections/profileprojection.h"

ProfileProjection::ProfileProjection() {}

QList<Vertex> ProfileProjection::Project(const QList<Vertex> &vertices)
{
    QList<Vertex> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Vertex vert;
        vert.SetPosition(vertices[i].GetPosition().GetZ(),
                         vertices[i].GetPosition().GetY(),
                         vertices[i].GetPosition().GetX());
        val.push_back(vert);
    }
    return val;
}
