#include "graphics/projections/perspectiveprojection.h"
#include "math/Tools.h"
#include <math.h>

PerspectiveProjection::PerspectiveProjection(const float& d, const float& ro, const float& alpha, const float& beta)
{
    m_projectionMatrix.SetElementAt(0, 0, 1.0f);
    m_projectionMatrix.SetElementAt(1, 1, 1.0f);
    m_projectionMatrix.SetElementAt(2, 2, 1.0f);
    if (d == 0.0f) m_projectionMatrix.SetElementAt(2, 3, 1.0f);
    else m_projectionMatrix.SetElementAt(2, 3, 1.0f / d);

    m_viewMatrix.SetElementAt(0, 0, -sinf(Tools::degToRad(alpha)));
    m_viewMatrix.SetElementAt(0, 1, -(cosf(Tools::degToRad(beta))*cosf(Tools::degToRad(alpha))));
    m_viewMatrix.SetElementAt(0, 2, -(sinf(Tools::degToRad(beta))*cosf(Tools::degToRad(alpha))));
    m_viewMatrix.SetElementAt(1, 0, cosf(Tools::degToRad(alpha)));
    m_viewMatrix.SetElementAt(1, 1, -(cosf(Tools::degToRad(beta))*sinf(Tools::degToRad(alpha))));
    m_viewMatrix.SetElementAt(1, 2, -(sinf(Tools::degToRad(beta))*sinf(Tools::degToRad(alpha))));
    m_viewMatrix.SetElementAt(2, 1, sinf(Tools::degToRad(beta)));
    m_viewMatrix.SetElementAt(2, 2, -cosf(Tools::degToRad(beta)));
    m_viewMatrix.SetElementAt(3, 2, ro);
    m_viewMatrix.SetElementAt(3, 3, 1.0f);
}

QList<Vertex> PerspectiveProjection::Project(const QList<Vertex> &vertices)
{
    QList<Vertex> val;
    for (int i = 0; i < vertices.length(); i++)
    {
        Vector3D tempVec = vertices[i].GetPosition();
        if (abs(tempVec.GetZ()) < 0.1f) tempVec.SetZ(0.1f);
        tempVec *= m_viewMatrix * m_projectionMatrix;
        tempVec.ToCartesian();
        Vertex vert;
        vert.SetPosition(tempVec.GetX(), tempVec.GetY(), vertices[i].GetPosition().GetZ());
        val.push_back(vert);
    }
    return val;
}
