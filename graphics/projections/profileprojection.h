#ifndef PROFILEPROJECTION_H
#define PROFILEPROJECTION_H

#include "graphics/projections/projection.h"

class ProfileProjection : public Projection
{
public:
    ProfileProjection();

    QList<Vertex> Project(const QList<Vertex> &vertices) override;
};

#endif // PROFILEPROJECTION_H
