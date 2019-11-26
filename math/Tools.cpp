#include "Tools.h"

float Tools::degToRad(const float& deg)
{
    return deg * (3.14159f / 180.0f);
}

float Tools::scaleInRange(const float &value, const float &oldMin, const float &oldMax, const float &newMin, const float &newMax)
{
    return ((value - oldMin)/(oldMax - oldMin)) * (newMax - newMin) + newMin;
}

float Tools::clamp(const float &value, const float &minVal, const float &maxVal)
{
    return max(minVal, min(value , maxVal));
}

int Tools::clamp(const int &value, const int &minVal, const int &maxVal)
{
    return max(minVal, min(value , maxVal));
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
