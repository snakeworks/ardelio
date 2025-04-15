#include "physics_space_2d.h"

PhysicsSpace2D::PhysicsSpace2D() : _gravity({ 0.0f, 1000.0f }), _drag{ 0.05f, 0.001f }, _drag_rotational{ 0.01f, 0.01f } {}

void PhysicsSpace2D::set_gravity(const Vector2& v) {
    _gravity = v;
}

void PhysicsSpace2D::set_drag(const Vector2& v) {
    _drag = v;
}

void PhysicsSpace2D::set_drag_rotational(const Vector2& v) {
    _drag_rotational = v;
}

void PhysicsSpace2D::add_body(PhysicsBody2D *body) {
    _bodies.push_back(body);
}

bool PhysicsSpace2D::is_at_rest() {
    float err = 2.0f;
    for (PhysicsBody2D *o : _bodies) {
        float v = o->get_velocity().magnitude();
        if (v > err) {
            return false;
        }
    }
    return true;
}

void PhysicsSpace2D::circle_vs_circle_collision(PhysicsBody2D *o, PhysicsBody2D *p) {
    float distance = p->get_global_position_2d().distance(o->get_global_position_2d());
    float radius_sum = p->get_shape().get_radius() + o->get_shape().get_radius();
    float dx = distance - radius_sum;

    if (dx <= 0) {
        Vector2 normal = p->get_global_position_2d() - o->get_global_position_2d();
        Vector2 tangent = normal.get_normal();
        Vector2 normalUnit = normal.normalized();
        Vector2 tangentUnit = tangent.normalized();

        // Reverse the Body to resolve the collision 
        Vector2 reverse = normalUnit * dx;
        Vector2 reverse_i_j = { reverse.dot({ 1.0f, 0.0f }) + reverse.dot({ 1.0f, 0.0f }), reverse.dot({ 0.0f, 1.0f }) + reverse.dot({ 0.0f, 1.0f }) };
        o->set_temp_position(o->get_temp_position() + reverse_i_j);

        // Velocity is uneffected parallel to tangent
        float tangent_speed = o->get_velocity().dot(tangentUnit);
        Vector2 tangent_velocity = tangentUnit * tangent_speed;

        // Initial velocity along normal
        float normal_speed_o = o->get_velocity().dot(normalUnit);
        float normal_speed_p = p->get_velocity().dot(normalUnit);

        // Conservation of momentum and kinetic energy - elastic collision
        float normal_speed_after_o = normal_speed_o * (o->get_mass() - p->get_mass()) / (o->get_mass() + p->get_mass()) + normal_speed_p * (2.0f * p->get_mass()) / (o->get_mass() + p->get_mass());
        Vector2 normal_velocity = normalUnit * normal_speed_after_o;
        Vector2 normal_velocity_i_j = { tangent_velocity.dot({1.0f, 0.0f}) + normal_velocity.dot({1.0f, 0.0f}) , tangent_velocity.dot({0.0f, 1.0f}) + normal_velocity.dot({0.0f, 1.0f}) };
        o->set_temp_velocity(normal_velocity_i_j);

        // Avoid PhysicsSpace2D::getting stuck
        float stuck = 0.01f;
        if ((abs(p->get_global_position_2d().x - o->get_global_position_2d().x) < stuck) && (abs(p->get_global_position_2d().y - o->get_global_position_2d().y) < stuck)) {
            o->set_temp_position({ o->get_global_position_2d().x - (o->get_shape().get_radius() + 0.1f), o->get_global_position_2d().y });
            p->set_temp_position({ o->get_global_position_2d().x + (p->get_shape().get_radius() + 0.1f), o->get_global_position_2d().y });
        }
    }
}

void PhysicsSpace2D::circle_vs_rectangle_collision(PhysicsBody2D *o, PhysicsBody2D *p, bool circle) {
    Vector2 pos_o;
    Vector2 len_o;
    Vector2 pos_p;
    Vector2 len_p;

    // TODO: COULD BE WRONG???
    if (circle) {
        pos_o = o->get_global_position_2d();
        len_o = o->get_shape().get_radius();
        pos_p = p->get_global_position_2d();
        len_p = p->get_shape().get_size() / 2.0f;
    } else {
        pos_p = p->get_global_position_2d();
        len_p = p->get_shape().get_radius();
        pos_o = o->get_global_position_2d();
        len_o = o->get_shape().get_size() / 2.0f;
    }

    bool condition = pos_o.x - len_o.x < pos_p.x + len_p.x && pos_o.x + len_o.x > pos_p.x - len_p.x &&
        pos_o.y - len_o.y < pos_p.y + len_p.y && pos_o.y + len_o.y > pos_p.y - len_p.y;

    if (condition) {
        float dx = (len_p.x + len_o.x) - abs(pos_p.x - pos_o.x);
        float dy = (len_p.y + len_o.y) - abs(pos_p.y - pos_o.y);

        Vector2 reverse_i_j;
        Vector2 normalUnit;

        // Resolve towards the smallest
        if (dx <= dy) {
            if (pos_o.x < pos_p.x) {
                normalUnit = { -1.0f, 0.0f };
                reverse_i_j = normalUnit * dx;
            } else {
                normalUnit = { 1.0f, 0.0f };
                reverse_i_j = normalUnit * dx;
            }
        }
        else {
            if (pos_o.y < pos_p.y) {
                normalUnit = { 0.0f, -1.0f };
                reverse_i_j = normalUnit * dy;
            } else {
                normalUnit = { 0.0f, 1.0f };
                reverse_i_j = normalUnit * dy;
            }
        }
        o->set_temp_position(o->get_temp_position() + reverse_i_j);

        // Velocity is uneffected parallel to tangent
        Vector2 tangentUnit = normalUnit.get_normal();
        float tangent_speed = o->get_velocity().dot(tangentUnit);
        Vector2 tangent_velocity = tangentUnit * tangent_speed;

        // Initial velocity along normal
        float normal_speed_o = o->get_velocity().dot(normalUnit);
        float normal_speed_p = p->get_velocity().dot(normalUnit);

        // Conservation of momentum and kinetic energy - elastic collision
        float normal_speed_after_o = normal_speed_o * (o->get_mass() - p->get_mass()) / (o->get_mass() + p->get_mass()) + normal_speed_p * (2.0f * p->get_mass()) / (o->get_mass() + p->get_mass());
        Vector2 normal_velocity = normalUnit * normal_speed_after_o;

        Vector2 velocity_i_j = normal_velocity + tangent_velocity;
        o->set_temp_velocity(velocity_i_j);

        // Temporary angular impulse
        int r = rand() % 2;
        float ang_velocity = (r == 0) ? velocity_i_j.magnitude() : -velocity_i_j.magnitude();
        o->set_theta_dot(ang_velocity / 2.0f);
    }
}

void PhysicsSpace2D::rectangle_vs_rectangle_collision(PhysicsBody2D *o, PhysicsBody2D *p) {
    Vector2 pos_o = o->get_global_position_2d();
    Vector2 len_o = o->get_shape().get_size() / 2.0f;
    Vector2 pos_p = p->get_global_position_2d();
    Vector2 len_p = p->get_shape().get_size() / 2.0f;

    bool condition = pos_o.x - len_o.x < pos_p.x + len_p.x && pos_o.x + len_o.x > pos_p.x - len_p.x &&
                        pos_o.y - len_o.y < pos_p.y + len_p.y && pos_o.y + len_o.y > pos_p.y - len_p.y;

    if (condition) {
        // Calculate penetration depth
        float dx = (len_p.x + len_o.x) - abs(pos_p.x - pos_o.x);
        float dy = (len_p.y + len_o.y) - abs(pos_p.y - pos_o.y);

        Vector2 correction;
        Vector2 normal_unit;

        // Resolve along the axis of least penetration
        if (dx <= dy) {
            if (pos_o.x < pos_p.x) {
                normal_unit = { -1.0f, 0.0f };
                correction = normal_unit * dx;
            } else {                  
                normal_unit = { 1.0f, 0.0f };
                correction = normal_unit * dx;
            }
        } else {
            if (pos_o.y < pos_p.y) {
                normal_unit = { 0.0f, -1.0f };
                correction = normal_unit * dy;
            } else {
                normal_unit = { 0.0f, 1.0f };
                correction = normal_unit * dy;
            }
        }

        // Apply positional correction (using a small bias factor to prevent jitter)
        const float bias_factor = 0.2f;
        Vector2 correction_i_j = correction * bias_factor;

        // Distribute correction based on mass (if not static)
        if (!o->get_static() && !p->get_static()) {
            float totalMass = o->get_mass() + p->get_mass();
            o->set_temp_position(o->get_temp_position() + correction_i_j * (p->get_mass() / totalMass));
            p->set_temp_position(p->get_temp_position() - correction_i_j * (o->get_mass() / totalMass));
        } else if (!o->get_static()) {
            o->set_temp_position(o->get_temp_position() + correction_i_j);
        } else if (!p->get_static()) {
            p->set_temp_position(p->get_temp_position() - correction_i_j);
        }

        // Velocity resolution with restitution
        Vector2 tangent_unit = normal_unit.get_normal();
        float tangent_speed = o->get_velocity().dot(tangent_unit);
        Vector2 tangent_velocity = tangent_unit * tangent_speed;

        float normal_speed_o = o->get_velocity().dot(normal_unit);
        float normal_speed_p = p->get_velocity().dot(normal_unit);

        // Calculate combined restitution
        float combined_restitution = o->get_restitution() * p->get_restitution();

        float normal_speed_after_o = (normal_speed_o * (o->get_mass() - p->get_mass()) + 
                                     2.0f * p->get_mass() * normal_speed_p) / 
                                     (o->get_mass() + p->get_mass());
        
        // Apply restitution
        normal_speed_after_o *= combined_restitution;
        
        Vector2 normal_velocity = normal_unit * normal_speed_after_o;

        Vector2 velocity_i_j = normal_velocity + tangent_velocity;
        o->set_temp_velocity(velocity_i_j);
    }
}

void PhysicsSpace2D::physics_update(float delta) {
    // Apply forces
    for (PhysicsBody2D *o : _bodies) {
        if (o->get_static()) {
            continue;
        }
        
        // Gravity
        o->set_acceleration(_gravity);

        //drag
        float speed = o->get_velocity().magnitude();
        Vector2 velocity_unit = o->get_velocity().normalized();
        o->apply_force(velocity_unit * speed * -_drag.x);
        o->apply_force(velocity_unit * speed * speed * -_drag.y);

        // Rotational drag
        float ang_speed = abs(o->get_theta_dot());
        float ang_velocityUnit = (o->get_theta_dot() < 0) ? -1.0f : 1.0f;
        o->apply_itheta_dot_dot(ang_velocityUnit * ang_speed * -_drag_rotational.x);
        o->apply_itheta_dot_dot(ang_velocityUnit * ang_speed * ang_speed * -_drag_rotational.y);
    }

    // Euler integrator
    for (PhysicsBody2D *o : _bodies) {
        // Linear
        Vector2 acc = o->get_acceleration() + o->get_force() / o->get_mass();
        o->set_velocity(o->get_velocity() + acc * delta);
        o->set_global_position_2d(o->get_global_position_2d() + o->get_velocity() * delta);

        o->set_force({ 0.0, 0.0 });
        o->set_acceleration({ 0.0, 0.0 });

        // Angular
        float angular_acc = o->get_theta_dot_dot() + o->get_itheta_dot_dot() / o->get_intertia();
        o->set_theta_dot(o->get_theta_dot() + angular_acc * delta);
        o->set_rotation(o->get_rotation() + o->get_theta_dot() * delta);

        o->set_itheta_dot_dot(0.0f);
        o->set_theta_dot_dot(0.0f);
    }

    // Collision detection
    // First Compute whole system on temp variables
    for (PhysicsBody2D *o : _bodies) {
        o->set_temp_velocity(o->get_velocity());
        o->set_temp_position(o->get_global_position_2d());
    }

    for (PhysicsBody2D *o : _bodies) {
        // Static Bodies can be targets (collided with and resolved from), but are not resolved themselves.
        if (o->get_static()) {
            continue;
        }

        for (PhysicsBody2D *p : _bodies) {
            if (o == p) {
                continue;
            }

            if (o->get_shape().is_circle() && p->get_shape().is_circle()) {
                circle_vs_circle_collision(o, p);
            } else if (o->get_shape().is_circle() && p->get_shape().is_rectangle()) {
                circle_vs_rectangle_collision(o, p, true);
            } else if (o->get_shape().is_rectangle() && p->get_shape().is_circle()) {
                circle_vs_rectangle_collision(o, p, false);
            } else if (o->get_shape().is_rectangle() && p->get_shape().is_rectangle()) {
                rectangle_vs_rectangle_collision(o, p);
            }
        }
    }

    for (PhysicsBody2D *o : _bodies) {
        o->set_velocity(o->get_temp_velocity());
        o->set_global_position_2d(o->get_temp_position());

        // Clamp velocity to zero for slow very Bodies
        if (o->get_velocity().magnitude() < 0.01f) {
            o->set_velocity({ 0.0f, 0.0f });
        }
        if (abs(o->get_theta_dot()) < 0.01f) {
            o->set_theta_dot(0.0f);
        }
    }
}