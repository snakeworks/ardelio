#pragma once

#include "game_object.h"

class Player2D : public GameObject {
public:
    Player2D(const std::string &name);
    void update(float delta) override;
    float speed;
};