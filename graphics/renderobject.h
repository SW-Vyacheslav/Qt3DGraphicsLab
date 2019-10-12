#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <QObject>
#include "math/Matrix4x4.h"
#include "graphics/mesh.h"
#include "graphics/vertex.h"
#include "math/Vector3D.h"

class RenderObject : public QObject
{
    Q_OBJECT

public:
    explicit RenderObject(QObject* parent = nullptr);
    virtual ~RenderObject();

    void Translate(const float& x, const float& y, const float& z);
    void Scale(const float& x, const float& y, const float& z);
    void Rotate(const float& x, const float& y, const float& z);
    void RotateByXAxis(const float& angle);
    void RotateByYAxis(const float& angle);
    void RotateByZAxis(const float& angle);

    Mesh& GetMesh();
    Vector3D GetPosition() const;
    void SetPosition(const Vector3D& position);
    void SetPosition(const float& x, const float& y, const float& z);

signals:
    void PositionChanged(Vector3D position);

private:
    Mesh m_mesh;
    Vector3D m_position;

    Matrix4x4 m_translateMat;
    Matrix4x4 m_scaleMat;
    Matrix4x4 m_rotXMat;
    Matrix4x4 m_rotYMat;
    Matrix4x4 m_rotZMat;
};

#endif // RENDEROBJECT_H
