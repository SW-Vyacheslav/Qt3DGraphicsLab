#include "graphics/projections/obliqueprojection.h"
#include "math/Tools.h"
#include <math.h>

ObliqueProjection::ObliqueProjection(const float& alpha, const float& l)
{
    m_projectionMatrix.SetElementAt(0, 0, 1.0f);
    m_projectionMatrix.SetElementAt(1, 1, 1.0f);
    m_projectionMatrix.SetElementAt(2, 0, l * cosf(Tools::degToRad(alpha)));
    m_projectionMatrix.SetElementAt(2, 1, l * sinf(Tools::degToRad(alpha)));
    m_projectionMatrix.SetElementAt(3, 3, 1.0f);

    //for z buffer
    m_projectionMatrix.SetElementAt(2, 2, 1.0f);
}

QList<Vertex> ObliqueProjection::Project(const QList<Vertex> &vertices)
{
    QList<Vertex> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Vector3D tempVec = vertices[i].GetPosition() * m_projectionMatrix;
        Vertex vert;
        vert.SetPosition(tempVec);
        val.push_back(vert);
    }
    return val;
}
