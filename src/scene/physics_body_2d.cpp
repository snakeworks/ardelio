#include "physics_body_2d.h"

PhysicsBody2D::PhysicsBody2D(const std::string &name, const CollisionShape &shape) : GameObject(name), _shape(shape), _static(false), _mass(1.0f), 
    _theta_dot(0.0f), _theta_dot_dot(0.0f), _itheta_dot_dot(0.0f), _inertia(1.0f),  _restitution(0.9f)
{}

void PhysicsBody2D::reset() {
    set_velocity({ 0.0f, 0.0f }); 
}

void PhysicsBody2D::reset(const Vector2 &v) {
    set_global_position({v.x, v.y, get_global_position().z});
    set_velocity({ 0.0f, 0.0f });
}

CollisionShape PhysicsBody2D::get_shape() const {
    return _shape;
}

void PhysicsBody2D::set_shape(const CollisionShape &new_shape) {
    _shape = new_shape;
}

Vector2 PhysicsBody2D::get_temp_position() { 
    return _temp_position; 
}
void PhysicsBody2D::set_temp_position(const Vector2& v) { 
    _temp_position = v; 
}

Vector2 PhysicsBody2D::get_velocity() const { 
    return _velocity; 
}

void PhysicsBody2D::set_velocity(const Vector2& v) { 
    _velocity = v; 
}

Vector2 PhysicsBody2D::get_temp_velocity() const { 
    return _temp_velocity; 
}

void PhysicsBody2D::set_temp_velocity(const Vector2& v) { 
    _temp_velocity = v; 
}

Vector2 PhysicsBody2D::get_acceleration() const { 
    return _acceleration; 
}

void PhysicsBody2D::set_acceleration(const Vector2& v) { 
    _acceleration = v; 
}

void PhysicsBody2D::apply_acceleration(const Vector2& v) { 
    _acceleration = _acceleration + v; 
}

Vector2 PhysicsBody2D::get_force() const { 
    return _force; 
}

void PhysicsBody2D::set_force(const Vector2& v) { 
    _force = v; 
}

void PhysicsBody2D::apply_force(const Vector2& v) { 
    _force = _force + v; 
}

float PhysicsBody2D::get_theta_dot() const { 
    return _theta_dot; 
}

void PhysicsBody2D::set_theta_dot(float t) { 
    _theta_dot = t; 
}

float PhysicsBody2D::get_theta_dot_dot() const { 
    return _theta_dot_dot; 
}

void PhysicsBody2D::set_theta_dot_dot(float t) { 
    _theta_dot_dot = t; 
}

float PhysicsBody2D::get_itheta_dot_dot() const { 
    return _itheta_dot_dot; 
}

void PhysicsBody2D::set_itheta_dot_dot(float t) { 
    _itheta_dot_dot = t; 
}

void PhysicsBody2D::apply_theta_dot_dot(float t) { 
    _theta_dot_dot = _theta_dot_dot + t; 
}

void PhysicsBody2D::apply_itheta_dot_dot(float t) { 
    _itheta_dot_dot = _itheta_dot_dot + t; 
}

float PhysicsBody2D::get_intertia() const { 
    return _inertia; 
}

float PhysicsBody2D::get_mass() const { 
    return _mass; 
}

float PhysicsBody2D::get_restitution() const { 
    return _restitution; 
}

bool PhysicsBody2D::get_static() const { 
    return _static; 
}

void PhysicsBody2D::set_static(bool new_static) { 
    _static = new_static; 
}