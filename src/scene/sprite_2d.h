#pragma once

#include "game_object.h"
#include "math/color.h"
#include "math/vector2u.h"
#include "resources/texture.h"

#include <string>
#include <SFML/Graphics.hpp>

class Sprite2D : public GameObject {
public:
    Sprite2D(const std::string &name, Texture &texture);
    void render(sf::RenderTarget *target) override;

    const Vector2U &get_size() const;
    void set_size(const Vector2U &new_size);
    
    const Texture &get_texture() const;
    void set_texture(const Texture &new_texture);
    
    const Color &get_modulate() const;
    void set_modulate(const Color &new_color);

    virtual std::vector<Property> get_property_list() override;
private:
    Texture _texture;
    Color _modulate;
    Vector2U _size;
    sf::Sprite _sf_sprite;
};