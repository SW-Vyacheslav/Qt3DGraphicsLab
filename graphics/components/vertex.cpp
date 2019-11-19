#include "vertex.h"

Vertex::Vertex(){}

Vertex::Vertex(const Vertex &vertex)
{
    m_position = vertex.m_position;
    m_uv = vertex.m_uv;
}

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

void Vertex::SetUV(const Vector2D& uv)
{
    m_uv = uv;
}

void Vertex::SetUV(const float &u, const float &v)
{
    m_uv.SetX(u);
    m_uv.SetY(v);
}

Vector3D Vertex::GetPosition() const
{
    return m_position;
}

Vector2D Vertex::GetUV() const
{
    return m_uv;
}
