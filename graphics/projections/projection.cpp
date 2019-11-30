#include "graphics/projections/projection.h"
#include "graphics/components/transformmatrixcreator.h"
#include "math/Tools.h"
#include <cassert>

Projection::Projection()
{

}

Projection::~Projection() {}

Matrix4x4 Projection::CreateOrthographicMatrix(const int& left, const int& right, const int& top, const int& bottom, const int& near, const int& far)
{
    assert(right != left);
    assert(top != bottom);
    assert(near != far);
    Matrix4x4 ret_val;
    ret_val.SetElementAt(0, 0, 2.0f / static_cast<float>(right - left));
    ret_val.SetElementAt(1, 1, 2.0f / static_cast<float>(top - bottom));
    ret_val.SetElementAt(2, 2, -2.0f / static_cast<float>(far - near));
    ret_val.SetElementAt(3, 0, -(static_cast<float>(right + left) / static_cast<float>(right - left)));
    ret_val.SetElementAt(3, 1, -(static_cast<float>(top + bottom) / static_cast<float>(top - bottom)));
    ret_val.SetElementAt(3, 2, -(static_cast<float>(far + near) / static_cast<float>(far - near)));
    ret_val.SetElementAt(3, 3, 1.0f);
    return ret_val;
}

ProjectionMatrix Projection::CreateProfileMatrix()
{
    ProjectionMatrix pm;
    pm.type = ProjectionMatrix::PROFILE;
    pm.viewPosition = Vector3D(-1000.0f, 0.0f, 0.0f);
    pm.projectionMatrix.SetElementAt(2, 0, -1.0f);
    pm.projectionMatrix.SetElementAt(1, 1, 1.0f);
    pm.projectionMatrix.SetElementAt(0, 2, 1.0f);
    pm.projectionMatrix.SetElementAt(3, 3, 1.0f);
    return pm;
}

ProjectionMatrix Projection::CreateFrontalMatrix()
{
    ProjectionMatrix pm;
    pm.type = ProjectionMatrix::FRONTAL;
    pm.viewPosition = Vector3D(0.0f, 0.0f, -1000.0f);
    pm.projectionMatrix = Matrix4x4::CreateIdentityMatrix();
    return pm;
}

ProjectionMatrix Projection::CreateHorizontalMatrix()
{
    ProjectionMatrix pm;
    pm.type = ProjectionMatrix::HORIZONTAL;
    pm.viewPosition = Vector3D(0.0f, 1000.0f, 0.0f);
    pm.projectionMatrix.SetElementAt(0, 0, 1.0f);
    pm.projectionMatrix.SetElementAt(2, 1, 1.0f);
    pm.projectionMatrix.SetElementAt(1, 2, -1.0f);
    pm.projectionMatrix.SetElementAt(3, 3, 1.0f);
    return pm;
}

ProjectionMatrix Projection::CreateObliqueMatrix(const float &alpha, const float &l)
{
    ProjectionMatrix pm;
    pm.type = ProjectionMatrix::OBLIQUE;
    pm.viewPosition = Vector3D(0.0f, 0.0f, -1000.0f);
    pm.viewTransformMatrix = Matrix4x4::CreateIdentityMatrix();
    pm.projectionMatrix.SetElementAt(0, 0, 1.0f);
    pm.projectionMatrix.SetElementAt(1, 1, 1.0f);
    pm.projectionMatrix.SetElementAt(2, 0, l * cosf(Tools::degToRad(alpha)));
    pm.projectionMatrix.SetElementAt(2, 1, l * sinf(Tools::degToRad(alpha)));
    pm.projectionMatrix.SetElementAt(2, 2, 1.0f);
    pm.projectionMatrix.SetElementAt(3, 3, 1.0f);
    return pm;
}

ProjectionMatrix Projection::CreateAxonometrixMatrix(const float &alpha, const float &beta)
{
    ProjectionMatrix pm;
    pm.type = ProjectionMatrix::AXONOMETRIC;
    pm.viewPosition = Vector3D(0.0f, 0.0f, -1000.0f);
    pm.projectionMatrix.SetElementAt(0, 0, cosf(Tools::degToRad(alpha)));
    pm.projectionMatrix.SetElementAt(0, 1, sinf(Tools::degToRad(beta)) * sinf(Tools::degToRad(alpha)));
    pm.projectionMatrix.SetElementAt(1, 1, cosf(Tools::degToRad(beta)));
    pm.projectionMatrix.SetElementAt(2, 0, sinf(Tools::degToRad(alpha)));
    pm.projectionMatrix.SetElementAt(2, 1, -(cosf(Tools::degToRad(alpha) * sinf(Tools::degToRad(beta)))));
    pm.projectionMatrix.SetElementAt(3, 3, 1.0f);
    pm.projectionMatrix.SetElementAt(2, 2, cosf(Tools::degToRad(beta)));
    pm.projectionMatrix.SetElementAt(1, 2, cosf(Tools::degToRad(alpha) * sinf(Tools::degToRad(beta))));
    pm.projectionMatrix.SetElementAt(0, 2, sinf(Tools::degToRad(beta)) * sinf(Tools::degToRad(alpha)));
    return pm;
}

ProjectionMatrix Projection::CreatePerspectiveMatrix(const float &d, const float &ro, const float &alpha, const float &beta)
{
    ProjectionMatrix pm;
    pm.type = ProjectionMatrix::PERSPECTIVE;
    pm.viewPosition = Vector3D(ro*sinf(Tools::degToRad(beta))*cosf(Tools::degToRad(alpha)),
                               ro*sinf(Tools::degToRad(beta))*sinf(Tools::degToRad(alpha)),
                               ro*cosf(Tools::degToRad(beta)));
    pm.projectionMatrix.SetElementAt(0, 0, 1.0f);
    pm.projectionMatrix.SetElementAt(1, 1, 1.0f);
    pm.projectionMatrix.SetElementAt(2, 2, 1.0f);
    if (d == 0.0f) pm.projectionMatrix.SetElementAt(2, 3, 0.001f);
    else pm.projectionMatrix.SetElementAt(2, 3, 1.0f / d);

    pm.viewTransformMatrix.SetElementAt(0, 0, -sinf(Tools::degToRad(alpha)));
    pm.viewTransformMatrix.SetElementAt(0, 1, -(cosf(Tools::degToRad(beta))*cosf(Tools::degToRad(alpha))));
    pm.viewTransformMatrix.SetElementAt(0, 2, -(sinf(Tools::degToRad(beta))*cosf(Tools::degToRad(alpha))));
    pm.viewTransformMatrix.SetElementAt(1, 0, cosf(Tools::degToRad(alpha)));
    pm.viewTransformMatrix.SetElementAt(1, 1, -(cosf(Tools::degToRad(beta))*sinf(Tools::degToRad(alpha))));
    pm.viewTransformMatrix.SetElementAt(1, 2, -(sinf(Tools::degToRad(beta))*sinf(Tools::degToRad(alpha))));
    pm.viewTransformMatrix.SetElementAt(2, 1, sinf(Tools::degToRad(beta)));
    pm.viewTransformMatrix.SetElementAt(2, 2, -cosf(Tools::degToRad(beta)));
    pm.viewTransformMatrix.SetElementAt(3, 2, ro);
    pm.viewTransformMatrix.SetElementAt(3, 3, 1.0f);
    return pm;
}
