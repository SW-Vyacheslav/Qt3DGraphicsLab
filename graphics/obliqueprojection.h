#ifndef OBLIQUEPROJECTION_H
#define OBLIQUEPROJECTION_H

#include "iprojection.h"
#include "math/Matrix4x4.h"

class ObliqueProjection : public IProjection
{
public:
    ObliqueProjection(const float& alpha, const float& l);
    ~ObliqueProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex> &vertices) override;

private:
    Matrix4x4 m_projectionMatrix;
};

#endif // OBLIQUEPROJECTION_H
