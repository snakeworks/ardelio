#pragma once

#include "Resource.h"
#include <SFML/Graphics.hpp>

class Texture : public Resource
{
public:
    Texture(const char *path);
    sf::Texture sfTexture;
};