#include "light.h"
#include "math/Tools.h"

Light::Light() : m_intensity(100)
{}

Light::Light(const Light &light)
{
    m_color = light.m_color;
    m_intensity = light.m_intensity;
}

Light::Light(const ColorN &color) : m_intensity(100), m_color(color)
{}

void Light::setPosition(const Vector3D &position)
{
    m_position = position;
}

void Light::setIntensity(const int &intensity)
{
    m_intensity = Tools::clamp(intensity, 0, 100);
}

void Light::setColor(const ColorN &color)
{
    m_color = color;
}

Vector3D Light::getPosition() const
{
    return m_position;
}

int Light::getIntensity() const
{
    return m_intensity;
}

ColorN Light::getColor() const
{
    return m_color;
}
