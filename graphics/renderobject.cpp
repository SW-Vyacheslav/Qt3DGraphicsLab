#include "renderobject.h"
#include "math/Matrix4x4.h"
#include "math/Converter.h"
#include <math.h>

RenderObject::RenderObject()
{
    m_translateMat.SetElementAt(0, 0, 1.0f);
    m_translateMat.SetElementAt(1, 1, 1.0f);
    m_translateMat.SetElementAt(2, 2, 1.0f);
    m_translateMat.SetElementAt(3, 3, 1.0f);

    m_scaleMat.SetElementAt(3, 3, 1.0f);

    m_rotXMat.SetElementAt(0, 0, 1.0f);
    m_rotXMat.SetElementAt(3, 3, 1.0f);

    m_rotYMat.SetElementAt(1, 1, 1.0f);
    m_rotYMat.SetElementAt(3, 3, 1.0f);

    m_rotZMat.SetElementAt(2, 2, 1.0f);
    m_rotZMat.SetElementAt(3, 3, 1.0f);
}

RenderObject::~RenderObject() {}

void RenderObject::Translate(const float& x, const float& y, const float& z)
{
    m_translateMat.SetElementAt(3, 0, x);
    m_translateMat.SetElementAt(3, 1, y);
    m_translateMat.SetElementAt(3, 2, z);

    for (int i = 0; i < m_mesh.GetVerticesNum(); i++)
    {
        Vertex& temp = m_mesh.GetVertex(i);
        temp.SetPosition(temp.GetPosition() * m_translateMat);
    }
}

void RenderObject::Scale(const float& x, const float& y, const float& z)
{
    m_scaleMat.SetElementAt(0, 0, x);
    m_scaleMat.SetElementAt(1, 1, y);
    m_scaleMat.SetElementAt(2, 2, z);

    for (int i = 0; i < m_mesh.GetVerticesNum(); i++)
    {
        Vertex& temp = m_mesh.GetVertex(i);
        temp.SetPosition(temp.GetPosition() * m_scaleMat);
    }
}

void RenderObject::Rotate(const float &x, const float &y, const float &z)
{
    RotateByZAxis(z);
    RotateByYAxis(y);
    RotateByXAxis(x);
}

void RenderObject::RotateByXAxis(const float& angle)
{
    m_rotXMat.SetElementAt(1, 1, cosf(Converter::DegreesToRadians(angle)));
    m_rotXMat.SetElementAt(1, 2, -sinf(Converter::DegreesToRadians(angle)));
    m_rotXMat.SetElementAt(2, 1, sinf(Converter::DegreesToRadians(angle)));
    m_rotXMat.SetElementAt(2, 2, cosf(Converter::DegreesToRadians(angle)));

    for (int i = 0; i < m_mesh.GetVerticesNum(); i++)
    {
        Vertex& temp = m_mesh.GetVertex(i);
        temp.SetPosition(temp.GetPosition() * m_rotXMat);
    }
}

void RenderObject::RotateByYAxis(const float& angle)
{
    m_rotYMat.SetElementAt(0, 0, cosf(Converter::DegreesToRadians(angle)));
    m_rotYMat.SetElementAt(0, 2, sinf(Converter::DegreesToRadians(angle)));
    m_rotYMat.SetElementAt(2, 0, -sinf(Converter::DegreesToRadians(angle)));
    m_rotYMat.SetElementAt(2, 2, cosf(Converter::DegreesToRadians(angle)));

    for (int i = 0; i < m_mesh.GetVerticesNum(); i++)
    {
        Vertex& temp = m_mesh.GetVertex(i);
        temp.SetPosition(temp.GetPosition() * m_rotYMat);
    }
}

void RenderObject::RotateByZAxis(const float& angle)
{
    m_rotZMat.SetElementAt(0, 0, cosf(Converter::DegreesToRadians(angle)));
    m_rotZMat.SetElementAt(0, 1, -sinf(Converter::DegreesToRadians(angle)));
    m_rotZMat.SetElementAt(1, 0, sinf(Converter::DegreesToRadians(angle)));
    m_rotZMat.SetElementAt(1, 1, cosf(Converter::DegreesToRadians(angle)));

    for (int i = 0; i < m_mesh.GetVerticesNum(); i++)
    {
        Vertex& temp = m_mesh.GetVertex(i);
        temp.SetPosition(temp.GetPosition() * m_rotZMat);
    }
}

Mesh& RenderObject::GetMesh()
{
    return m_mesh;
}
