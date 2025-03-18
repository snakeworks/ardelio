#pragma once

#include "game_object.h"

#include <string>
#include <SFML/Graphics.hpp>

class Sprite2D : public GameObject {
public:
    Sprite2D(const std::string &name);
};