#ifndef OBLIQUEPROJECTION_H
#define OBLIQUEPROJECTION_H

#include "graphics/projections/projection.h"
#include "math/Matrix4x4.h"

class ObliqueProjection : public Projection
{
public:
    ObliqueProjection(const float& alpha, const float& l);

    QList<Vertex> Project(const QList<Vertex> &vertices) override;

private:
    Matrix4x4 m_projectionMatrix;
};

#endif // OBLIQUEPROJECTION_H
