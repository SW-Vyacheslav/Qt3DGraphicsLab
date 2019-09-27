#ifndef HORIZONTALPROJECTION_H
#define HORIZONTALPROJECTION_H

#include "projection.h"
#include "point.h"

class HorizontalProjection : public Projection
{
public:
    HorizontalProjection();
    ~HorizontalProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex>& vertices) override;
};

#endif // HORIZONTALPROJECTION_H
