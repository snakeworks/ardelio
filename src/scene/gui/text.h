#pragma once

#include "gui_element.h"
#include "resources/font.h"

#include <SFML/Graphics.hpp>

class Text : public GUIElement {
public:
    Text(const std::string &name, const std::string &text, const Font *font);

    void render(sf::RenderTarget *target) override;

    std::string get_text() const;
    void set_text(const std::string &new_text);

    uint32_t get_font_size() const;
    void set_font_size(uint32_t new_size);
private:
    std::string _text;
    sf::Text _sf_text;
    uint32_t _font_size;
};