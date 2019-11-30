#ifndef PROJECTION_H
#define PROJECTION_H

#include <QList>
#include "graphics/components/vertex.h"
#include "graphics/projections/projectionmatrix.h"

class Projection
{
public:
    Projection();

    virtual ~Projection();

    __declspec(deprecated)
    virtual QList<Vertex> Project(const QList<Vertex>& vertices) = 0;

    static Matrix4x4 CreateOrthographicMatrix(const int& left, const int& right, const int& top, const int& bottom, const int& near, const int& far);
    static ProjectionMatrix CreateProfileMatrix();
    static ProjectionMatrix CreateFrontalMatrix();
    static ProjectionMatrix CreateHorizontalMatrix();
    static ProjectionMatrix CreateObliqueMatrix(const float& alpha, const float& l);
    static ProjectionMatrix CreateAxonometrixMatrix(const float& alpha, const float& beta);
    static ProjectionMatrix CreatePerspectiveMatrix(const float& d, const float& ro, const float& alpha, const float& beta);
};

#endif // PROJECTION_H
