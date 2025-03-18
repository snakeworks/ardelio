#pragma once

struct Vector3 {
public:
    Vector3(float x = 0, float y = 0, float z = 0);
    float x, y, z;
    
    static Vector3 zero;
    static Vector3 one;
    static Vector3 up;
    static Vector3 down;
    static Vector3 forward;
    static Vector3 back;
    static Vector3 right;
    static Vector3 left;

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
};