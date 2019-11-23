#include "transformmatrixcreator.h"
#include "math/Tools.h"
#include <math.h>

Matrix4x4 TransformMatrixCreator::CreateTranslateMatrix(const float &x, const float &y, const float &z)
{
    Matrix4x4 val;
    val.SetElementAt(0, 0, 1.0f);
    val.SetElementAt(1, 1, 1.0f);
    val.SetElementAt(2, 2, 1.0f);
    val.SetElementAt(3, 0, x);
    val.SetElementAt(3, 1, y);
    val.SetElementAt(3, 2, z);
    val.SetElementAt(3, 3, 1.0f);
    return val;
}

Matrix4x4 TransformMatrixCreator::CreateScaleMatrix(const float &x, const float &y, const float &z)
{
    Matrix4x4 val;
    val.SetElementAt(0, 0, x);
    val.SetElementAt(1, 1, y);
    val.SetElementAt(2, 2, z);
    val.SetElementAt(3, 3, 1.0f);
    return val;
}

Matrix4x4 TransformMatrixCreator::CreateRotateMatrix(const float &x, const float &y, const float &z)
{
    return CreateRotateByZAxisMatrix(z) * CreateRotateByYAxisMatrix(y) * CreateRotateByXAxisMatrix(x);
}

Matrix4x4 TransformMatrixCreator::CreateRotateByXAxisMatrix(const float &angle)
{
    Matrix4x4 val;
    val.SetElementAt(0, 0, 1.0f);
    val.SetElementAt(1, 1, cosf(Tools::degToRad(angle)));
    val.SetElementAt(1, 2, -sinf(Tools::degToRad(angle)));
    val.SetElementAt(2, 1, sinf(Tools::degToRad(angle)));
    val.SetElementAt(2, 2, cosf(Tools::degToRad(angle)));
    val.SetElementAt(3, 3, 1.0f);
    return val;
}

Matrix4x4 TransformMatrixCreator::CreateRotateByYAxisMatrix(const float &angle)
{
    Matrix4x4 val;
    val.SetElementAt(1, 1, 1.0f);
    val.SetElementAt(0, 0, cosf(Tools::degToRad(angle)));
    val.SetElementAt(0, 2, sinf(Tools::degToRad(angle)));
    val.SetElementAt(2, 0, -sinf(Tools::degToRad(angle)));
    val.SetElementAt(2, 2, cosf(Tools::degToRad(angle)));
    val.SetElementAt(3, 3, 1.0f);
    return val;
}

Matrix4x4 TransformMatrixCreator::CreateRotateByZAxisMatrix(const float &angle)
{
    Matrix4x4 val;
    val.SetElementAt(0, 0, cosf(Tools::degToRad(angle)));
    val.SetElementAt(0, 1, -sinf(Tools::degToRad(angle)));
    val.SetElementAt(1, 0, sinf(Tools::degToRad(angle)));
    val.SetElementAt(1, 1, cosf(Tools::degToRad(angle)));
    val.SetElementAt(2, 2, 1.0f);
    val.SetElementAt(3, 3, 1.0f);
    return val;
}
