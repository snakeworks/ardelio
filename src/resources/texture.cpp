#include "texture.h"

Texture::Texture() : Resource("") {
    sf::Image white_image({32u, 32u}, sf::Color::White);
    sf::Texture default_texture;
    bool _ = default_texture.loadFromImage(white_image);
    _sf_texture = default_texture;
}

Texture::Texture(const std::string &path) : Resource(path) {
    try {
        _sf_texture = sf::Texture(path);
    } catch(const std::exception &e) {
        sf::Image white_image({32u, 32u}, sf::Color::White);
        sf::Texture default_texture;
        bool _ = default_texture.loadFromImage(white_image);
        _sf_texture = default_texture;
    }
}

sf::Texture &Texture::get_sf_texture() {
    return _sf_texture;
}