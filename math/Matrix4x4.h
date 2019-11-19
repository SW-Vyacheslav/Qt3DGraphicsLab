#ifndef MATRIX4X4_H
#define MATRIX4X4_H

class Matrix4x4
{
public:
    Matrix4x4();
    Matrix4x4(const Matrix4x4& mat);

    void SetElementAt(const int& row, const int& column, const float& val);
    float GetElementAt(const int& row, const int& column) const;

    static Matrix4x4 CreateIdentityMatrix();

    Matrix4x4 operator*(const Matrix4x4& mat);
    void operator*=(const Matrix4x4& mat);

private:
    float m_elements[16];
};

#endif
