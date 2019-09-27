#ifndef VERTEX_H
#define VERTEX_H

#include "math/Vector3D.h"
#include "point.h"

class Vertex
{
public:
    Vertex();

    void SetPosition(const Vector3D& position);
    void SetPosition(const float& x, const float& y, const float& z);
    void SetNormal(const Vector3D& normal);
    void SetNormal(const float& x, const float& y, const float& z);
    void SetUV(const Point& uv);
    void SetUV(const float& x, const float& y);

    Vector3D GetPosition() const;
    Vector3D GetNormal() const;
    Point GetUV() const;

private:
    Vector3D m_position;
    Vector3D m_normal;
    Point m_uv;
};

#endif // VERTEX_H
