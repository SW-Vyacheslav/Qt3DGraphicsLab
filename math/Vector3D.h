#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Matrix4x4.h"

class Vector3D
{
public:
    Vector3D();
    Vector3D(const float& x, const float& y, const float& z);
    Vector3D(const Vector3D& vec);

    void SetX(const float& x);
    void SetY(const float& y);
    void SetZ(const float& z);
    void SetW(const float& w);
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetW() const;

    float GetLength() const;
    Vector3D GetNormalized() const;
    void Normalize();
    Vector3D GetCartesian() const;
    void ToCartesian();

    static float DotProduct(const Vector3D& vec1, const Vector3D& vec2);
    static Vector3D CrossProduct(const Vector3D& vec1, const Vector3D& vec2);

    Vector3D operator-();
    Vector3D operator+(const Vector3D& vec);
    void operator+=(const Vector3D& vec);
    Vector3D operator-(const Vector3D& vec);
    void operator-=(const Vector3D& vec);
    Vector3D operator*(const float& num);
    void operator*=(const float& num);
    Vector3D operator*(const Matrix4x4& mat);
    void operator*=(const Matrix4x4& mat);

private:
    float x;
    float y;
    float z;
    float w;
};

#endif
