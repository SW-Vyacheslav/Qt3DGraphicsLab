#ifndef HORIZONTALPROJECTION_H
#define HORIZONTALPROJECTION_H

#include "graphics/projections/projection.h"

class HorizontalProjection : public Projection
{
public:
    HorizontalProjection();
    ~HorizontalProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex>& vertices) override;
};

#endif // HORIZONTALPROJECTION_H
