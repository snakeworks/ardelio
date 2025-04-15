#pragma once

#include "resource.h"

#include <SFML/Graphics.hpp>

class Font : public Resource {
public:
    Font(const std::string &path);
    const sf::Font &get_sf_font() const;
private:
    sf::Font _sf_font;
};