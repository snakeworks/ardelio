#include "text.h"
#include "engine/engine.h"

Text::Text(const std::string &name)
    : GUIElement(name), _text(""), 
    // TODO: Lmao, what is this nonsense
    _sf_text((new Font(std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of('/')) + "/../../misc/Roboto-Medium.ttf"))->get_sf_font()), 
    _font_size(16) {
    set_text("Text");

    const std::string group_name = "text";
    static std::string text = get_text();
    _property_list.push_back(
        Property(
            "text", group_name,
            [this]() {
                return Variant(VariantType::STRING, &text);
            },
            [this](Variant variant) {
                text = variant.as_string();
                set_text(text);
            }
        )
    );
    _property_list.push_back(
        Property(
            "font_size", group_name,
            [this]() {
                float font_size = get_font_size();
                return Variant(VariantType::FLOAT, &font_size);
            },
            [this](Variant variant) {
                set_font_size(variant.as_float());
            }
        )
    );
    _property_list.push_back(
        Property(
            "modulate", group_name,
            [this]() {
                Color modulate = get_modulate();
                return Variant(VariantType::COLOR, &modulate);
            },
            [this](Variant variant) {
                set_modulate(variant.as_color());
            }
        )
    );
}

void Text::render(sf::RenderTarget *target) {
    _sf_text.setFillColor(get_modulate().get_sf_color());
    sf::FloatRect text_bounds = _sf_text.getLocalBounds();
    _sf_text.setOrigin({text_bounds.size.x / 2.0f, text_bounds.size.y / 2.0f});
    _sf_text.setPosition({get_global_position().x, get_global_position().y});
    target->draw(_sf_text);
}

std::string Text::get_text() const {
    return _text;
}

void Text::set_text(const std::string &new_text) {
    _text = new_text;
    _sf_text.setString(_text);
    set_font_size(_font_size);
}

uint32_t Text::get_font_size() const {
    return _font_size;
}

void Text::set_font_size(uint32_t new_size) {
    _font_size = new_size;
    _sf_text.setCharacterSize(_font_size);
}

std::string Text::nameof_type() const {
    return NAMEOF(Text);
}
