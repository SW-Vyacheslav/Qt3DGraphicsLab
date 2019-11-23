#ifndef COLORN_H
#define COLORN_H

#include <QRgb>

class ColorN
{
public:
    ColorN(const ColorN& color);
    ColorN(const int& r = 0, const int& g = 0, const int& b = 0);

    float getRed() const;
    float getGreen() const;
    float getBlue() const;

    QRgb toRgb();

private:
    float m_red;
    float m_green;
    float m_blue;
};

#endif // COLORN_H
