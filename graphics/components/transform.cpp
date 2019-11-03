#include "graphics/components/transform.h"
#include "transformmatrixcreator.h"

Transform::Transform() : QObject(nullptr)
{

}

void Transform::Translate(const float &x, const float &y, const float &z)
{
    m_position.SetX(m_position.GetX() + x);
    m_position.SetY(m_position.GetY() + y);
    m_position.SetZ(m_position.GetZ() + z);
    emit OnPositionChanged(m_position);
}

void Transform::Scale(const float &x, const float &y, const float &z)
{
    m_scale.SetX(m_scale.GetX() * x);
    m_scale.SetY(m_scale.GetY() * y);
    m_scale.SetZ(m_scale.GetZ() * z);
    emit OnScaleChanged(m_scale);
}

void Transform::Rotate(const float &x, const float &y, const float &z)
{
    m_rotation.SetX(m_rotation.GetX() + x);
    m_rotation.SetY(m_rotation.GetY() + y);
    m_rotation.SetZ(m_rotation.GetZ() + z);
    emit OnRotationChanged(m_rotation);
}

Vector3D Transform::GetPosition() const
{
    return m_position;
}

Vector3D Transform::GetRotation() const
{
    return m_rotation;
}

Vector3D Transform::GetScale() const
{
    return m_scale;
}

Vector3D Transform::GetOpPosition() const
{
    return m_opPosition;
}

void Transform::SetPivot(Transform::Pivot pivot)
{
    m_isUsePivot = true;
    m_pivot = pivot;
    emit OnPivotChanged(m_pivot);
}

void Transform::SetOpPosition(const Vector3D &position)
{
    m_isUsePivot = false;
    m_opPosition = position;
    emit OnOpPositionChanged(m_opPosition);
}

bool Transform::IsPivotUsed()
{
    return m_isUsePivot;
}

Transform::Pivot Transform::GetPivot() const
{
    return m_pivot;
}

void Transform::SetPosition(const Vector3D &position)
{
    m_position = position;
}

void Transform::SetRotation(const Vector3D &rotation)
{
    m_rotation = rotation;
}

void Transform::SetScale(const Vector3D &scale)
{
    m_scale = scale;
}
