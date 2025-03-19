#include "vector3.h"

#include <math.h>

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z) {}

const Vector3 Vector3::zero = Vector3(0, 0, 0);
const Vector3 Vector3::one = Vector3(1, 1, 1);
const Vector3 Vector3::up = Vector3(0, -1, 0);
const Vector3 Vector3::down = Vector3(0, 1, 0);
const Vector3 Vector3::forward = Vector3(0, 0, 1);
const Vector3 Vector3::back = Vector3(0, 0, -1);
const Vector3 Vector3::right = Vector3(1, 0, 0);
const Vector3 Vector3::left = Vector3(-1, 0, 0);

float Vector3::length() const {
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    return std::sqrt(x2 + y2 + z2);
}

float Vector3::length_squared() const {
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    return x2 + y2 + z2;
}

void Vector3::normalize() {
    float lq = length_squared();
    if (lq == 0) {
        x = y = z = 0;
    } else {
        float l = std::sqrt(lq);
        x /= l;
        y /= l;
        z /= l;
    }
}

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}