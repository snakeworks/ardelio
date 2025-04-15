#include "vector2.h"

#include <cmath>

Vector2::Vector2(float x, float y)
    : x(x), y(y) {}

const Vector2 Vector2::zero = Vector2(0, 0);
const Vector2 Vector2::one = Vector2(1, 1);
const Vector2 Vector2::up = Vector2(0, -1);
const Vector2 Vector2::down = Vector2(0, 1);
const Vector2 Vector2::right = Vector2(1, 0);
const Vector2 Vector2::left = Vector2(-1, 0);

Vector2 Vector2::operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const Vector2 &other) const {
    return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator/(const Vector2 &other) const {
    return Vector2(x / other.x, y / other.y); 
}

Vector2 operator/(int scalar, const Vector2 &vec) {
    return Vector2(scalar / vec.x, scalar / vec.y);
}

float Vector2::dot(const Vector2 &other) const {
    return x * other.x + y * other.y;
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::get_normal() const {
    return { -y, x };
}

Vector2 Vector2::normalized() const {
    float m = length();
    return (m > 0) ? *this / m : Vector2();
}

float Vector2::distance(const Vector2 &other) const {
    return{ std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y)) };
}