#ifndef VERTEX_H
#define VERTEX_H

#include "math/Vector3D.h"
#include "QPointF"

class Vertex
{
public:
    Vertex();

    void SetPosition(const Vector3D& position);
    void SetNormal(const Vector3D& normal);
    void SetUV(const QPointF& uv);

    Vector3D& GetPosition();
    Vector3D& GetNormal();
    QPointF& GetUV();

private:
    Vector3D m_position;
    Vector3D m_normal;
    QPointF m_uv;
};

#endif // VERTEX_H
