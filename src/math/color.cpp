#include "color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) 
    : r(r), g(g), b(b), a(a), _sf_color(sf::Color(r, g, b, a)) {}

    const Color Color::white = Color(255, 255, 255, 255);
    const Color Color::black = Color(0, 0, 0, 255);

const sf::Color &Color::get_sf_color() const {
    return _sf_color;
}
