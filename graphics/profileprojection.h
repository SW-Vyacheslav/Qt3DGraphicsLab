#ifndef PROFILEPROJECTION_H
#define PROFILEPROJECTION_H

#include "iprojection.h"

class ProfileProjection : public IProjection
{
public:
    ProfileProjection();
    ~ProfileProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex> &vertices) override;
};

#endif // PROFILEPROJECTION_H
