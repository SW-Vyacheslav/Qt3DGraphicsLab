#include "graphics/projections/frontalprojection.h"

FrontalProjection::FrontalProjection() {}

FrontalProjection::~FrontalProjection() {}

QList<Vertex> FrontalProjection::Project(const QList<Vertex> &vertices)
{
    return vertices;
}
