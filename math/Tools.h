#ifndef SWE_CONVERTER
#define SWE_CONVERTER

class Tools
{
public:
    static float degToRad(const float& deg);
    static float scaleInRange(const float& value, const float& oldMin, const float& oldMax, const float& newMin, const float& newMax);

    static float clamp(const float& value, const float& minVal, const float& maxVal);
    static int clamp(const int& value, const int& minVal, const int& maxVal);

    static float min(const float& a, const float& b);
    static int min(const int& a, const int& b);

    static float max(const float& a, const float& b);
    static int max(const int& a, const int& b);

    template<typename T>
    static inline void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
};

#endif
