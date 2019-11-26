#ifndef PERSPECTIVEPROJECTION_H
#define PERSPECTIVEPROJECTION_H

#include "graphics/projections/projection.h"
#include "math/Matrix4x4.h"

class PerspectiveProjection : public Projection
{
public:
    PerspectiveProjection(const float& d, const float& ro, const float& alpha, const float& beta);

    QList<Vertex> Project(const QList<Vertex> &vertices) override;

private:
    Matrix4x4 m_projectionMatrix;
    Matrix4x4 m_viewMatrix;
};

#endif // PERSPECTIVEPROJECTION_H
