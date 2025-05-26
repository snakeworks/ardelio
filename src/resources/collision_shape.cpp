#include "collision_shape.h"

CollisionShape::CollisionShape(Vector2 size) : Resource(""), _size(size), _radius(-1.0f) {}
CollisionShape::CollisionShape(float radius) : Resource(""), _size(Vector2::zero), _radius(radius) {}

bool CollisionShape::is_rectangle() {
    return _radius <= 0.0f;
}

bool CollisionShape::is_circle() {
    return _radius >= 0.0f;
}

Vector2 CollisionShape::get_size() const {
    return _size;
}

void CollisionShape::set_size(const Vector2 &new_size) {
    _size = new_size;
}

float CollisionShape::get_radius() const {
    return _radius;
}