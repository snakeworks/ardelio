#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

struct Color {
public:
    Color(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);
    uint8_t r, g, b, a;
    
    static const Color white;
    static const Color black;

    const sf::Color &get_sf_color() const;
private:
    sf::Color _sf_color;
};