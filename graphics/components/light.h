#ifndef LIGHT_H
#define LIGHT_H

#include "graphics/components/colorn.h"

class Light
{
public:
    Light();

    //void setIntensity(const int& intensity);

    //float getIntensity() const;

private:
    int m_intensity;
    ColorN m_color;
};

#endif // LIGHT_H
