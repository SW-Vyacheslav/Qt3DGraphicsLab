#ifndef VERTEX_H
#define VERTEX_H

#include "math/Vector3D.h"
#include "math/Vector2D.h"

class Vertex
{
public:
    Vertex();
    Vertex(const Vertex& vertex);

    void SetPosition(const Vector3D& position);
    void SetPosition(const float& x, const float& y, const float& z);
    void SetUV(const Vector2D& uv);
    void SetUV(const float& u, const float& v);

    Vector3D GetPosition() const;
    Vector2D GetUV() const;

private:
    Vector3D m_position;
    Vector2D m_uv;
};

#endif // VERTEX_H
