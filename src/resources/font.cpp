#include "font.h"

Font::Font(const std::string &path) : Resource(path) {
    _sf_font = sf::Font(path);
}

const sf::Font &Font::get_sf_font() const {
    return _sf_font;
}