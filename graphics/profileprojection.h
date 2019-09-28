#ifndef PROFILEPROJECTION_H
#define PROFILEPROJECTION_H

#include "projection.h"

class ProfileProjection : public Projection
{
public:
    ProfileProjection();
    ~ProfileProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex> &vertices) override;
};

#endif // PROFILEPROJECTION_H
