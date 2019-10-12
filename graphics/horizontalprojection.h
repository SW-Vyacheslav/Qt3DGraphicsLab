#ifndef HORIZONTALPROJECTION_H
#define HORIZONTALPROJECTION_H

#include "iprojection.h"

class HorizontalProjection : public IProjection
{
public:
    HorizontalProjection();
    ~HorizontalProjection() override;

    QList<Point> GetProjectionPoints(const QList<Vertex>& vertices) override;
};

#endif // HORIZONTALPROJECTION_H
