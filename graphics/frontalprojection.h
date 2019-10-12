#ifndef FRONTALPROJECTION_H
#define FRONTALPROJECTION_H

#include "iprojection.h"

class FrontalProjection : public IProjection
{
public:
    FrontalProjection();
    ~FrontalProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex>& vertices) override;
};

#endif // FRONTALPROJECTION_H
