#include "graphics/projections/horizontalprojection.h"

HorizontalProjection::HorizontalProjection() {}

QList<Vertex> HorizontalProjection::Project(const QList<Vertex>& vertices)
{
    QList<Vertex> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Vertex vert;
        vert.SetPosition(vertices[i].GetPosition().GetX(),
                         vertices[i].GetPosition().GetZ(),
                         vertices[i].GetPosition().GetY());
        val.push_back(vert);
    }
    return val;
}
