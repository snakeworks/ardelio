#pragma once

#include "resource.h"

#include <SFML/Graphics.hpp>

class Texture : public Resource {
public:
    Texture(const std::string &path);
    const sf::Texture &get_sf_texture() const;
private:
    sf::Texture _sf_texture;
};