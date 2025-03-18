#include "sprite_2d.h"

Sprite2D::Sprite2D(const std::string &name, Texture &texture) 
    : GameObject(name), _texture(texture), _sf_sprite(_texture.get_sf_texture()) {}

void Sprite2D::render(sf::RenderWindow *window) {
    window->draw(_sf_sprite);
}

const Texture &Sprite2D::get_texture() const {
    return _texture;
}

void Sprite2D::set_texture(const Texture &new_texture) {
    _texture = new_texture;
    _sf_sprite.setTexture(_texture.get_sf_texture());
}

