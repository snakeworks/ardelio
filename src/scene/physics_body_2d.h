#pragma once

#include "game_object.h"
#include "resources/collision_shape.h"

class PhysicsBody2D : public GameObject {
public:
    PhysicsBody2D(const std::string &name);

    void reset();
    void reset(const Vector2 &position);

    CollisionShape *get_shape() const;
    void set_shape(CollisionShape *new_shape);

    Vector2 get_temp_position();
    void set_temp_position(const Vector2 &new_temp_position);
    
    Vector2 get_velocity() const;
    void set_velocity(const Vector2 &new_velocity);
    Vector2 get_temp_velocity() const;
    void set_temp_velocity(const Vector2 &new_temp_velocity);
    
    Vector2 get_acceleration() const;
    void set_acceleration(const Vector2 &new_acceleration);
    void apply_acceleration(const Vector2 &applied_acceleration);
    
    Vector2 get_force() const;
    void set_force(const Vector2 &new_force);
    void apply_force(const Vector2 &applied_force);
    
    float get_theta_dot() const;
    void set_theta_dot(float new_theta_dot);
    
    float get_theta_dot_dot() const;
    void set_theta_dot_dot(float new_theta_dot_dot);
    void apply_theta_dot_dot(float applied_theta_dot_dot);
    
    float get_itheta_dot_dot() const;
    void set_itheta_dot_dot(float new_itheta_dot_dot);
    void apply_itheta_dot_dot(float applied_itheta_dot_dot);
    
    float get_mass() const;
    void set_mass(float new_mass);

    float get_intertia() const;
    float get_restitution() const;
    
    bool get_static() const;
    void set_static(bool new_static);

    virtual std::string nameof_type() const override;
protected:
    bool _static;
    
    CollisionShape *_shape;

    Vector2 _velocity;
    Vector2 _temp_position;
    Vector2 _temp_velocity;
    Vector2 _acceleration;
    Vector2 _force;
    
    float _mass;
    float _restitution;
    float _theta_dot;
    float _theta_dot_dot;
    float _itheta_dot_dot;
    float _inertia;
};