#ifndef THORUS_H
#define THORUS_H

#include "graphics/components/worldobject.h"

class Thorus : public WorldObject
{
public:
    Thorus();

    void Construct(const int& n, const int& m, const int& R, const int& r);
};

#endif // THORUS_H
