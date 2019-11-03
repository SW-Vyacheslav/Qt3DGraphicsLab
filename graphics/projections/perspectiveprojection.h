#ifndef PERSPECTIVEPROJECTION_H
#define PERSPECTIVEPROJECTION_H

#include "graphics/projections/projection.h"
#include "math/Matrix4x4.h"

class PerspectiveProjection : public Projection
{
public:
    PerspectiveProjection(const float& d);

    QList<Point> GetProjectionPoints(const QList<Vertex> &vertices) override;

private:
    Matrix4x4 m_projectionMatrix;
};

#endif // PERSPECTIVEPROJECTION_H
