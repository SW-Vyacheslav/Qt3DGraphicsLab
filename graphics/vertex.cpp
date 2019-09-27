#include "vertex.h"

Vertex::Vertex(){}

void Vertex::SetPosition(const Vector3D& position)
{
    m_position = position;
}

void Vertex::SetPosition(const float &x, const float &y, const float &z)
{
    m_position.SetX(x);
    m_position.SetY(y);
    m_position.SetZ(z);
}

void Vertex::SetNormal(const Vector3D& normal)
{
    m_normal = normal;
}

void Vertex::SetNormal(const float &x, const float &y, const float &z)
{
    m_normal.SetX(x);
    m_normal.SetY(y);
    m_normal.SetZ(z);
}

void Vertex::SetUV(const Point& uv)
{
    m_uv = uv;
}

Vector3D Vertex::GetPosition() const
{
    return m_position;
}

Vector3D Vertex::GetNormal() const
{
    return m_normal;
}

Point Vertex::GetUV() const
{
    return m_uv;
}
