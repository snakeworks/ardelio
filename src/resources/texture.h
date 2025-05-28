#pragma once

#include "resource.h"

#include <SFML/Graphics.hpp>

class Texture : public Resource {
public:
    Texture();
    Texture(const std::string &path);
    sf::Texture &get_sf_texture();
private:
    sf::Texture _sf_texture;
};