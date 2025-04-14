#pragma once

struct Vector2 {
public:
    Vector2(float x = 0, float y = 0);
    float x, y;

    static const Vector2 zero;
    static const Vector2 one;
    static const Vector2 up;
    static const Vector2 down;
    static const Vector2 right;
    static const Vector2 left;

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator*(const Vector2 &other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(const Vector2 &other) const;
    Vector2 operator/(float scalar) const;
    friend Vector2 operator/(int scalar, const Vector2 &vec);

    float dot(const Vector2 &other) const;
    float magnitude() const;
    Vector2 get_normal() const;
    Vector2 normalized() const;
    float distance(const Vector2 &other) const;
};