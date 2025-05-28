#include "sprite_2d.h"
#include "engine/engine.h"

std::string *property_path = nullptr;

Sprite2D::Sprite2D(const std::string &name) 
    : GameObject(name),
    _texture(new Texture()),
    _sf_sprite(_texture->get_sf_texture()),
    _modulate(Color::white) {
        property_path = new std::string(get_texture()->get_path());

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
        
        _property_list.push_back(
            Property("texture_path", group_name,
                [this]() {
                    return Variant(VariantType::STRING, property_path);
                },
                [this](Variant variant) { 
                    std::string path = variant.as_string();
                    if (this->get_texture() != nullptr && path == this->get_texture()->get_path()) {
                        return;
                    }
                    if (std::filesystem::exists(path)) {
                        if (property_path != nullptr) {
                            delete property_path;
                        }
                        property_path = new std::string(path);
                        Texture *new_texture = new Texture(*property_path);
                        this->set_texture(new_texture);
                    }
                }
            )  
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

Texture *Sprite2D::get_texture() const {
    return _texture;
}

void Sprite2D::set_texture(Texture *new_texture) {
    if (new_texture == nullptr) {
        return;
    }
    if (_texture != nullptr) {
        // TODO: Later change to ref counting
        delete _texture;
        _texture = nullptr;
    }
    _texture = new_texture;
    _sf_sprite.setTexture(_texture->get_sf_texture(), true);
}

const Color &Sprite2D::get_modulate() const {
    return _modulate;
}

void Sprite2D::set_modulate(const Color &new_color) {
    _modulate = new_color;
    _sf_sprite.setColor(_modulate.get_sf_color());
}

std::string Sprite2D::nameof_type() const {
    return NAMEOF(Sprite2D);
}
