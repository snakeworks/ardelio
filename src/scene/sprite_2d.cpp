#include "sprite_2d.h"

Texture *Sprite2D::_default_texture = new Texture("assets/white64x64.png");

Sprite2D::Sprite2D(const std::string &name) 
    : GameObject(name),
    _texture(_default_texture),
    _sf_sprite(_texture->get_sf_texture()),
    _modulate(Color::white) {
        auto sf_tex_size = _texture->get_sf_texture().getSize();
        set_size({
            static_cast<float>(sf_tex_size.x),
            static_cast<float>(sf_tex_size.y)
        });

        std::string group_name = "sprite_2d";
        _property_list.push_back(
            Property("modulate", group_name,
                [this]() {
                    Color modulate = this->get_modulate();
                    return Variant(VariantType::COLOR, &modulate);
                },
                [this](Variant variant) { this->set_modulate(variant.as_color()); })
        );
        _property_list.push_back(
            Property("size", group_name,
                [this]() {
                    Vector2 size = this->get_size();
                    return Variant(VariantType::VECTOR2, &size);
                },
                [this](Variant variant) { this->set_size(variant.as_vector2()); })
        );
}

void Sprite2D::render(sf::RenderTarget *target) {
    auto global_pos = get_global_position();
    _sf_sprite.setPosition({global_pos.x, global_pos.y});
    _sf_sprite.setRotation(sf::radians(get_global_rotation()));
    target->draw(_sf_sprite);
}

const Vector2 &Sprite2D::get_size() const {
    return _size;
}

void Sprite2D::set_size(const Vector2 &new_size) {
    _size = new_size;
    auto base_size = _texture->get_sf_texture().getSize();
    _sf_sprite.setScale({
        static_cast<float>(_size.x) / static_cast<float>(base_size.x),
        static_cast<float>(_size.y) / static_cast<float>(base_size.y)
    });
    _sf_sprite.setOrigin({_sf_sprite.getLocalBounds().size.x / 2.f, 
        _sf_sprite.getLocalBounds().size.y / 2.f});
}

const Texture *Sprite2D::get_texture() const {
    return _texture;
}

void Sprite2D::set_texture(Texture *new_texture) {
    _texture = new_texture;
    _sf_sprite.setTexture(_texture->get_sf_texture());
}

const Color &Sprite2D::get_modulate() const {
    return _modulate;
}

void Sprite2D::set_modulate(const Color &new_color) {
    _modulate = new_color;
    _sf_sprite.setColor(_modulate.get_sf_color());
}
