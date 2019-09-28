#include "obliqueprojection.h"
#include "math/Converter.h"
#include <math.h>

ObliqueProjection::ObliqueProjection(const float& alpha, const float& l)
{
    m_projectionMatrix.SetElementAt(0, 0, 1.0f);
    m_projectionMatrix.SetElementAt(1, 1, 1.0f);
    m_projectionMatrix.SetElementAt(2, 0, l * cosf(Converter::DegreesToRadians(alpha)));
    m_projectionMatrix.SetElementAt(2, 1, l * sinf(Converter::DegreesToRadians(alpha)));
    m_projectionMatrix.SetElementAt(3, 3, 1.0f);
}

ObliqueProjection::~ObliqueProjection() {}

QList<Point> ObliqueProjection::GetProjectionPoints(const QList<Vertex> &vertices)
{
    QList<Point> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Vector3D tempVec = vertices[i].GetPosition() * m_projectionMatrix;
        Point point;
        point.x = tempVec.GetX();
        point.y = tempVec.GetY();
        val.push_back(point);
    }
    return val;
}
