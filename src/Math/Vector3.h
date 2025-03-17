#pragma once

struct Vector3
{
public:
    Vector3(float x = 0, float y = 0, float z = 0);
    float x, y, z;

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
    Vector3 operator*(const float scalar) const;
};
