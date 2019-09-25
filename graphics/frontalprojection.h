#ifndef FRONTALPROJECTION_H
#define FRONTALPROJECTION_H

#include "projection.h"

class FrontalProjection : public Projection
{
public:
    FrontalProjection();

    QList<QPointF> GetProjectionPoints(QList<Vertex> vertices) override;
};

#endif // FRONTALPROJECTION_H
