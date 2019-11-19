#include "graphics/projections/axonometricprojection.h"
#include "math/Converter.h"
#include <math.h>

AxonometricProjection::AxonometricProjection(const float& alphaAngle, const float& betaAngle)
{
    m_projectionMatrix.SetElementAt(0, 0, cosf(Converter::DegreesToRadians(alphaAngle)));
    m_projectionMatrix.SetElementAt(0, 1, sinf(Converter::DegreesToRadians(betaAngle)) * sinf(Converter::DegreesToRadians(alphaAngle)));
    m_projectionMatrix.SetElementAt(1, 1, cosf(Converter::DegreesToRadians(betaAngle)));
    m_projectionMatrix.SetElementAt(2, 0, sinf(Converter::DegreesToRadians(alphaAngle)));
    m_projectionMatrix.SetElementAt(2, 1, -sinf(Converter::DegreesToRadians(betaAngle)) * cosf(Converter::DegreesToRadians(alphaAngle)));
    m_projectionMatrix.SetElementAt(3, 3, 1.0f);
}

AxonometricProjection::~AxonometricProjection() {}

QList<Vertex> AxonometricProjection::Project(const QList<Vertex> &vertices)
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
