#include "vector3.h"

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

Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}