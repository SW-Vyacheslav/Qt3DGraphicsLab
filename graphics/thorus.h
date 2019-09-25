#ifndef THORUS_H
#define THORUS_H

#include "graphics/renderobject.h"

class Thorus : public RenderObject
{
public:
    Thorus();

    void Construct(const int& n, const int& m, const int& R, const int& r);
};

#endif // THORUS_H
