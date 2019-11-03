#include "graphics/components/worldobject.h"

WorldObject::WorldObject()
{

}

WorldObject::~WorldObject()
{

}

Mesh& WorldObject::GetMesh()
{
    return m_mesh;
}

Transform& WorldObject::GetTransform()
{
    return m_transform;
}
