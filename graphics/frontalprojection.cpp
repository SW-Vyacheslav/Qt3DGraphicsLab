#include "frontalprojection.h"
#include "vertex.h"

FrontalProjection::FrontalProjection() {}

QList<QPointF> FrontalProjection::GetProjectionPoints(QList<Vertex> vertices)
{
    QList<QPointF> val;

    for (int i = 0; i < vertices.length(); i++)
    {
        QPointF point;
        point.setX(static_cast<double>(vertices[i].GetPosition().GetX()));
        point.setY(static_cast<double>(vertices[i].GetPosition().GetY()));
        val.push_back(point);
    }

    return val;
}
