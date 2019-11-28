#ifndef LIGHT_H
#define LIGHT_H

#include "graphics/components/colorn.h"
#include "math/Vector3D.h"

class Light
{
public:
    Light();
    Light(const Light& light);
    Light(const ColorN& color);

    void setPosition(const Vector3D& position);
    void setIntensity(const int& intensity);
    void setColor(const ColorN& color);
    Vector3D getPosition() const;
    int getIntensity() const;
    ColorN getColor() const;

private:
    Vector3D m_position;
    int m_intensity;
    ColorN m_color;
};

#endif // LIGHT_H
