#include "vertex.h"

Vertex::Vertex(){}

void Vertex::SetPosition(const Vector3D& position)
{
    m_position = position;
}

void Vertex::SetNormal(const Vector3D& normal)
{
    m_normal = normal;
}

void Vertex::SetUV(const QPointF& uv)
{
    m_uv = uv;
}

Vector3D& Vertex::GetPosition()
{
    return m_position;
}

Vector3D& Vertex::GetNormal()
{
    return m_normal;
}

QPointF& Vertex::GetUV()
{
    return m_uv;
}
