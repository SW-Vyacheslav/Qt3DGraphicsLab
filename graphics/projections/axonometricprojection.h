#ifndef AXONOMETRICPROJECTION_H
#define AXONOMETRICPROJECTION_H

#include "graphics/projections/projection.h"
#include "math/Matrix4x4.h"

class AxonometricProjection : public Projection
{
public:
    AxonometricProjection(const float& alphaAngle, const float& betaAngle);
    ~AxonometricProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex> &vertices) override;

private:
    Matrix4x4 m_projectionMatrix;
};

#endif // AXONOMETRICPROJECTION_H
