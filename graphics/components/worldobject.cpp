#include "graphics/components/worldobject.h"

WorldObject::WorldObject()
{

}

WorldObject::~WorldObject()
{

}

Transform& WorldObject::GetTransform()
{
    return m_transform;
}
