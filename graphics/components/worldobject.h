#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "graphics/components/mesh.h"
#include "graphics/components/transform.h"

class WorldObject
{

public:
    WorldObject();
    virtual ~WorldObject();

    Mesh& GetMesh();
    Transform& GetTransform();

private:
    Mesh m_mesh;
    Transform m_transform;
};

#endif // RENDEROBJECT_H
