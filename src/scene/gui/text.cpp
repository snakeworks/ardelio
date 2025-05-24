#include "text.h"

Text::Text(const std::string &name, const std::string &text, const Font *font)
    : GUIElement(name), _text(text), _sf_text(font->get_sf_font()), _font_size(16) {
    set_text(text);
}

void Text::render(sf::RenderTarget *target) {
    _sf_text.setFillColor(get_modulate().get_sf_color());
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
