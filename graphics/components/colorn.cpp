#include "colorn.h"

#include "math/Tools.h"

ColorN::ColorN(const ColorN &color)
{
    m_red = color.m_red;
    m_green = color.m_green;
    m_blue = color.m_blue;
}

ColorN::ColorN(const int &r, const int &g, const int &b)
{
    m_red = Tools::scaleInRange(Tools::clamp(r, 0, 255), 0, 255, 0, 1);
    m_green = Tools::scaleInRange(Tools::clamp(g, 0, 255), 0, 255, 0, 1);
    m_blue = Tools::scaleInRange(Tools::clamp(b, 0, 255), 0, 255, 0, 1);
}

float ColorN::getRed() const
{
    return m_red;
}

float ColorN::getGreen() const
{
    return m_green;
}

float ColorN::getBlue() const
{
    return m_blue;
}

void ColorN::setRed(const float &red)
{
    m_red = Tools::clamp(red, 0.0f, 1.0f);
}

void ColorN::setGreen(const float &green)
{
    m_green = Tools::clamp(green, 0.0f, 1.0f);
}

void ColorN::setBlue(const float &blue)
{
    m_blue = Tools::clamp(blue, 0.0f, 1.0f);
}

QRgb ColorN::toRgb()
{
    return qRgb(static_cast<int>(Tools::scaleInRange(m_red, 0, 1, 0, 255)),
             static_cast<int>(Tools::scaleInRange(m_green, 0, 1, 0, 255)),
             static_cast<int>(Tools::scaleInRange(m_blue, 0, 1, 0, 255)));
}
