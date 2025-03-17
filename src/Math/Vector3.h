#pragma once

class Vector3
{
public:
    Vector3(float x, float y, float z);
    float x, y, z;

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
};
