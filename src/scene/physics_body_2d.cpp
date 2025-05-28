#include "physics_body_2d.h"
#include "engine/engine.h"

PhysicsBody2D::PhysicsBody2D(const std::string &name) : GameObject(name), _shape(new CollisionShape({32.0f, 32.0f})), _static(false), _mass(1.0f), 
    _theta_dot(0.0f), _theta_dot_dot(0.0f), _itheta_dot_dot(0.0f), _inertia(1.0f),  _restitution(1.0f), _last_colliding_body(nullptr)
{
    const std::string group_name = "physics_body_2d";
    _property_list.push_back(
        Property(
            "is_static", group_name,
            [this]() {
                bool is_static = this->get_static();
                return Variant(VariantType::BOOL, &is_static);
            },
            [this](Variant variant) {
                this->set_static(variant.as_bool());       
            }
        )
    );
    _property_list.push_back(
        Property(
            "shape_size", group_name,
            [this]() {
                Vector2 size = this->get_shape()->get_size();
                return Variant(VariantType::VECTOR2, &size);
            },
            [this](Variant variant) {
                this->get_shape()->set_size(variant.as_vector2());
            }
        )
    );
}

void PhysicsBody2D::reset() {
    set_velocity(Vector2::zero);
}

void PhysicsBody2D::reset(const Vector2 &position) {
    set_global_position_2d(position);
    set_velocity(Vector2::zero);
}

CollisionShape *PhysicsBody2D::get_shape() const {
    return _shape;
}

void PhysicsBody2D::set_shape(CollisionShape *new_shape) {
    _shape = new_shape;
}

PhysicsBody2D *PhysicsBody2D::get_last_colliding_body() {
    return _last_colliding_body;
}

void PhysicsBody2D::set_last_colliding_body(PhysicsBody2D *body) {
    _last_colliding_body = body;
}

Vector2 PhysicsBody2D::get_temp_position() { 
    return _temp_position; 
}
void PhysicsBody2D::set_temp_position(const Vector2 &new_temp_position) { 
    _temp_position = new_temp_position; 
}

Vector2 PhysicsBody2D::get_velocity() const { 
    return _velocity; 
}

void PhysicsBody2D::set_velocity(const Vector2 &new_velocity) { 
    _velocity = new_velocity; 
}

Vector2 PhysicsBody2D::get_temp_velocity() const { 
    return _temp_velocity; 
}

void PhysicsBody2D::set_temp_velocity(const Vector2 &new_temp_velocity) { 
    _temp_velocity = new_temp_velocity; 
}

Vector2 PhysicsBody2D::get_acceleration() const { 
    return _acceleration; 
}

void PhysicsBody2D::set_acceleration(const Vector2 &new_acceleration) { 
    _acceleration = new_acceleration; 
}

void PhysicsBody2D::apply_acceleration(const Vector2 &applied_acceleration) { 
    _acceleration = _acceleration + applied_acceleration; 
}

Vector2 PhysicsBody2D::get_force() const { 
    return _force; 
}

void PhysicsBody2D::set_force(const Vector2 &new_force) { 
    _force = new_force; 
}

void PhysicsBody2D::apply_force(const Vector2 &applied_force) { 
    _force = _force + applied_force;
}

float PhysicsBody2D::get_theta_dot() const { 
    return _theta_dot; 
}

void PhysicsBody2D::set_theta_dot(float new_theta_dot) { 
    _theta_dot = new_theta_dot;
}

float PhysicsBody2D::get_theta_dot_dot() const { 
    return _theta_dot_dot; 
}

void PhysicsBody2D::set_theta_dot_dot(float new_theta_dot_dot) { 
    _theta_dot_dot = new_theta_dot_dot;
}

void PhysicsBody2D::apply_theta_dot_dot(float applied_theta_dot_dot) { 
    _theta_dot_dot = _theta_dot_dot + applied_theta_dot_dot;
}

float PhysicsBody2D::get_itheta_dot_dot() const { 
    return _itheta_dot_dot; 
}

void PhysicsBody2D::set_itheta_dot_dot(float new_itheta_dot_dot) { 
    _itheta_dot_dot = new_itheta_dot_dot;
}

void PhysicsBody2D::apply_itheta_dot_dot(float applied_itheta_dot_dot) { 
    _itheta_dot_dot = _itheta_dot_dot + applied_itheta_dot_dot;
}

float PhysicsBody2D::get_intertia() const { 
    return _inertia; 
}

float PhysicsBody2D::get_mass() const { 
    return _mass; 
}

void PhysicsBody2D::set_mass(float mass) {
    _mass = mass;
}

float PhysicsBody2D::get_restitution() const { 
    return _restitution; 
}

bool PhysicsBody2D::get_static() const { 
    return _static; 
}

void PhysicsBody2D::set_static(bool new_static) { 
    if (new_static == true) {
        set_velocity(Vector2::zero);
        set_temp_velocity(Vector2::zero);
    }
    _static = new_static;
}

std::string PhysicsBody2D::nameof_type() const {
    return NAMEOF(PhysicsBody2D);
}
