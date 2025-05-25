#pragma once

#include "game_object.h"
#include "math/color.h"
#include "math/vector2.h"
#include "resources/texture.h"

#include <string>
#include <SFML/Graphics.hpp>

class Sprite2D : public GameObject {
public:
    Sprite2D(const std::string &name);
    void render(sf::RenderTarget *target) override;

    const Vector2 &get_size() const;
    void set_size(const Vector2 &new_size);
    
    const Texture *get_texture() const;
    void set_texture(Texture *new_texture);
    
    const Color &get_modulate() const;
    void set_modulate(const Color &new_color);

    virtual std::string nameof_type() const override;
private:
    static Texture *_default_texture;
    Texture *_texture;
    Color _modulate;
    Vector2 _size;
    sf::Sprite _sf_sprite;
};