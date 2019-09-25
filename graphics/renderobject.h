#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "math/Matrix4x4.h"
#include "graphics/mesh.h"
#include "graphics/vertex.h"

class RenderObject
{
public:
    RenderObject();

    void Translate(const float& x, const float& y, const float& z);
    void Scale(const float& x, const float& y, const float& z);
    void Rotate(const float& x, const float& y, const float& z);
    void RotateByXAxis(const float& angle);
    void RotateByYAxis(const float& angle);
    void RotateByZAxis(const float& angle);

    Mesh& GetMesh();

private:
    Mesh m_mesh;

    Matrix4x4 m_translateMat;
    Matrix4x4 m_scaleMat;
    Matrix4x4 m_rotXMat;
    Matrix4x4 m_rotYMat;
    Matrix4x4 m_rotZMat;
};

#endif // RENDEROBJECT_H
