#ifndef PROJECTION_H
#define PROJECTION_H

#include "QPointF"
#include "QList"
#include "graphics/vertex.h"

class Projection
{
public:
    virtual ~Projection();

    virtual QList<QPointF> GetProjectionPoints(QList<Vertex> vertices) = 0;
};

#endif // PROJECTION_H
