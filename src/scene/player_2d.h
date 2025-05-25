#pragma once

#include "physics_body_2d.h"

class Player2D : public PhysicsBody2D {
public:
    Player2D(const std::string &name);
    void update(float delta) override;
    float speed;

    virtual std::string nameof_type() const override;
};