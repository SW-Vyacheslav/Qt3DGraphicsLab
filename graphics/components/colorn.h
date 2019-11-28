#ifndef COLORN_H
#define COLORN_H

#include <QRgb>

class ColorN
{
public:
    ColorN(const ColorN& color);
    ColorN(const int& r = 255, const int& g = 255, const int& b = 255);

    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    void setRed(const float& red);
    void setGreen(const float& green);
    void setBlue(const float& blue);

    QRgb toRgb();

private:
    float m_red;
    float m_green;
    float m_blue;
};

#endif // COLORN_H
