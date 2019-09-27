#ifndef PROJECTION_H
#define PROJECTION_H

#include <QList>
#include "point.h"
#include "vertex.h"

class Projection
{
public:
    virtual ~Projection();

    virtual QList<Point> GetProjectionPoints(const QList<Vertex>& vertices) = 0;
};

#endif // PROJECTION_H
