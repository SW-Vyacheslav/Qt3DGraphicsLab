#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QObject>
#include "math/Vector3D.h"
#include "math/Matrix4x4.h"

class Transform : public QObject
{
    Q_OBJECT

public:
    enum Pivot
    {
        CENTER,
        RIGHT,
        LEFT,
        UP,
        DOWN,
        UP_LEFT_CORNER,
        UP_RIGHT_CORNER,
        DOWN_LEFT_CORNER,
        DOWN_RIGHT_CORNER,
        USER_DEFINED
    };

    Transform();

    void Translate(const float& x, const float& y, const float& z);
    void Scale(const float& x, const float& y, const float& z);
    void Rotate(const float& x, const float& y, const float& z);

    Vector3D GetPosition() const;
    Vector3D GetRotation() const;
    Vector3D GetScale() const;
    Vector3D GetOpPosition() const;
    Pivot GetPivot() const;

public slots:
    void SetPivot(Pivot pivot);
    void SetOpPosition(const Vector3D& position);
    void SetPosition(const Vector3D& position);
    void SetRotation(const Vector3D &rotation);
    void SetScale(const Vector3D &scale);

signals:
    void OnPositionChanged(const Vector3D& newPosition);
    void OnRotationChanged(const Vector3D& newRotation);
    void OnScaleChanged(const Vector3D& newScale);
    void OnPivotChanged(Pivot newPivot);
    void OnOpPositionChanged(const Vector3D& newPosition);

private:
    Vector3D m_position;
    Vector3D m_rotation;
    Vector3D m_scale;
    Pivot m_pivot;
    Vector3D m_opPosition;
};

#endif // TRANSFORM_H
