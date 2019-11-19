#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "graphics/components/transform.h"

class WorldObject
{
public:
    WorldObject();
    virtual ~WorldObject();

    Transform& GetTransform();

private:
    Transform m_transform;
};

#endif // RENDEROBJECT_H
