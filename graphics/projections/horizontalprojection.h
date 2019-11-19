#ifndef HORIZONTALPROJECTION_H
#define HORIZONTALPROJECTION_H

#include "graphics/projections/projection.h"

class HorizontalProjection : public Projection
{
public:
    HorizontalProjection();

    QList<Vertex> Project(const QList<Vertex> &vertices) override;
};

#endif // HORIZONTALPROJECTION_H
