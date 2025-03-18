#pragma once

struct Vector3 {
public:
    Vector3(float x = 0, float y = 0, float z = 0);
    float x, y, z;
    
    static const Vector3 zero;
    static const Vector3 one;
    static const Vector3 up;
    static const Vector3 down;
    static const Vector3 forward;
    static const Vector3 back;
    static const Vector3 right;
    static const Vector3 left;

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
};