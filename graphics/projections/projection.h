#ifndef PROJECTION_H
#define PROJECTION_H

#include <QList>
#include "graphics/components/vertex.h"

class Projection
{
public:
    virtual ~Projection();

    virtual QList<Vertex> Project(const QList<Vertex>& vertices) = 0;
};

#endif // PROJECTION_H
