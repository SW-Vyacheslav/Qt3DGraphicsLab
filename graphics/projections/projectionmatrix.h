#ifndef PROJECTIONMATRIX_H
#define PROJECTIONMATRIX_H

#include "math/Matrix4x4.h"
#include "math/Vector3D.h"

struct ProjectionMatrix
{
    enum MatrixType
    {
        FRONTAL,
        HORIZONTAL,
        PROFILE,
        OBLIQUE,
        AXONOMETRIC,
        PERSPECTIVE
    };

    MatrixType type;
    Matrix4x4 projectionMatrix;
    Matrix4x4 viewTransformMatrix;
    Vector3D viewPosition;
};

#endif // PROJECTIONMATRIX_H
