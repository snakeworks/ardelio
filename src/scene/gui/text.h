#pragma once

#include "gui_element.h"
#include "resources/font.h"

#include <SFML/Graphics.hpp>

class Text : public GUIElement {
public:
    Text(const std::string &name);

    void render(sf::RenderTarget *target) override;

    std::string get_text() const;
    void set_text(const std::string &new_text);

    uint32_t get_font_size() const;
    void set_font_size(uint32_t new_size);

    virtual std::string nameof_type() const override;
private:
    std::string _text;
    sf::Text _sf_text;
    uint32_t _font_size;
    std::string *_property_text;
};