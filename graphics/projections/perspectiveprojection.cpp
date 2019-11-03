#include "graphics/projections/perspectiveprojection.h"
#include <math.h>

PerspectiveProjection::PerspectiveProjection(const float& d)
{
    m_projectionMatrix.SetElementAt(0, 0, 1.0f);
    m_projectionMatrix.SetElementAt(1, 1, 1.0f);
    m_projectionMatrix.SetElementAt(2, 2, 1.0f);
    if (d == 0.0f) m_projectionMatrix.SetElementAt(2, 3, 1.0f);
    else m_projectionMatrix.SetElementAt(2, 3, 1.0f / d);
}

QList<Point> PerspectiveProjection::GetProjectionPoints(const QList<Vertex> &vertices)
{
    QList<Point> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Vector3D tempVec = vertices[i].GetPosition();
        if (abs(tempVec.GetZ()) < 0.1f) tempVec.SetZ(0.1f);
        tempVec *= m_projectionMatrix;
        tempVec.ToCartesian();
        Point point;
        point.x = tempVec.GetX();
        point.y = tempVec.GetY();
        val.push_back(point);
    }
    return val;
}
