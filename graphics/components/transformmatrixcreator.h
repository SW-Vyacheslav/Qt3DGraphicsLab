#ifndef TRANSFORMMATRIXCREATOR_H
#define TRANSFORMMATRIXCREATOR_H

#include "math/Matrix4x4.h"

class TransformMatrixCreator
{
public:
    static Matrix4x4 CreateTranslateMatrix(const float& x, const float& y, const float& z);
    static Matrix4x4 CreateScaleMatrix(const float& x, const float& y, const float& z);
    static Matrix4x4 CreateRotateMatrix(const float& x, const float& y, const float& z);
    static Matrix4x4 CreateRotateByXAxisMatrix(const float& angle);
    static Matrix4x4 CreateRotateByYAxisMatrix(const float& angle);
    static Matrix4x4 CreateRotateByZAxisMatrix(const float& angle);
};

#endif // TRANSFORMMATRIXCREATOR_H
