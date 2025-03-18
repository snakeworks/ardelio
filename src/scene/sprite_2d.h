#pragma once

#include "game_object.h"
#include "math/color.h"
#include "resources/texture.h"

#include <string>
#include <SFML/Graphics.hpp>

class Sprite2D : public GameObject {
public:
    Sprite2D(const std::string &name, Texture &texture);
    void render(sf::RenderWindow *window) override;

    const Texture &get_texture() const;
    void set_texture(const Texture &new_texture);

    const Color &get_modulate() const;
    void set_modulate(const Color &new_color);
private:
    Texture _texture;
    Color _modulate;
    sf::Sprite _sf_sprite;
};