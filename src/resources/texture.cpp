#include "texture.h"

Texture::Texture(const std::string &path) : Resource(path) {
    _sf_texture = sf::Texture(path);
} 

const sf::Texture &Texture::get_sf_texture() const {
    return _sf_texture;
}