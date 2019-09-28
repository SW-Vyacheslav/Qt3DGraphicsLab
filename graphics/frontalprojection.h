#ifndef FRONTALPROJECTION_H
#define FRONTALPROJECTION_H

#include "projection.h"

class FrontalProjection : public Projection
{
public:
    FrontalProjection();
    ~FrontalProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex>& vertices) override;
};

#endif // FRONTALPROJECTION_H
