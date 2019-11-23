#include "Tools.h"

float Tools::degToRad(const float& deg)
{
    return deg * (3.14159f / 180.0f);
}

float Tools::scaleInRange(const float &value, const float &oldMin, const float &oldMax, const float &newMin, const float &newMax)
{
    return ((value - oldMin)/(oldMax - oldMin)) * (newMax - newMin) + newMin;
}

float Tools::clamp(const float &value, const float &min, const float &max)
{
    return Tools::max(min, Tools::min(value , max));
}

int Tools::clamp(const int &value, const int &min, const int &max)
{
    return Tools::max(min, Tools::min(value , max));
}

float Tools::min(const float &a, const float &b)
{
    return (a < b) ? a : b;
}

int Tools::min(const int &a, const int &b)
{
    return (a < b) ? a : b;
}

float Tools::max(const float &a, const float &b)
{
    return (a > b) ? a : b;
}

int Tools::max(const int &a, const int &b)
{
    return (a > b) ? a : b;
}
