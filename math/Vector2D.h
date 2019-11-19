#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    Vector2D();
    Vector2D(const float& x, const float& y);
    Vector2D(const Vector2D& vec);

    void SetX(const float& x);
    void SetY(const float& y);
    void SetW(const float& w);
    float GetX() const;
    float GetY() const;
    float GetW() const;

    float GetLength() const;
    Vector2D Normalize() const;

    static float DotProduct(const Vector2D& vec1, const Vector2D& vec2);

    Vector2D operator+(const Vector2D& vec);
    void operator+=(const Vector2D& vec);
    Vector2D operator-(const Vector2D& vec);
    void operator-=(const Vector2D& vec);
    Vector2D operator*(const float& num);
    void operator*=(const float& num);

private:
    float x;
    float y;
    float w;
};

#endif
