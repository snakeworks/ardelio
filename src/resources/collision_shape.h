#pragma once

#include "resource.h"
#include "math/vector2.h"

struct CollisionShape : public Resource {
public:
    CollisionShape(Vector2 size);
    CollisionShape(float radius);

    bool is_rectangle();
    bool is_circle();

    Vector2 get_size() const;
    float get_radius() const;

private:
    Vector2 _size;
    float _radius; 
};