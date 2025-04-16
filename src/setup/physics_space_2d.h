#pragma once

#include "physics_space_2d.h"
#include "math/vector2.h"
#include "scene/physics_body_2d.h"
#include "resources/collision_shape.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class PhysicsSpace2D {
public:
    PhysicsSpace2D();

	void set_gravity(const Vector2& v);
	void set_drag(const Vector2& v);
	void set_drag_rotational(const Vector2& v);

	void add_body(PhysicsBody2D *body);
	void remove_body(PhysicsBody2D *body);

	bool is_at_rest();

	void circle_vs_circle_collision(PhysicsBody2D *o, PhysicsBody2D *p);
	void circle_vs_rectangle_collision(PhysicsBody2D* o, PhysicsBody2D* p, bool circle);
	void rectangle_vs_rectangle_collision(PhysicsBody2D* o, PhysicsBody2D* p);

	void physics_update(float delta);

private:
	std::vector<PhysicsBody2D*> _bodies;
	Vector2 _gravity;
	Vector2 _drag;
	Vector2 _drag_rotational;
};