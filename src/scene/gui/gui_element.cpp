#include "gui_element.h"

GUIElement::GUIElement(const std::string &name) 
    : GameObject(name), _modulate(Color::white) {}

Color GUIElement::get_modulate() const {
    return _modulate;
}

void GUIElement::set_modulate(const Color &new_modulate) {
    _modulate = new_modulate;
}