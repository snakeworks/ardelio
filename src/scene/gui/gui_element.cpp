#include "gui_element.h"

GUIElement::GUIElement(const std::string &name) 
    : GameObject(name), _modulate(Color::white), _size(Vector2::zero) {}

Vector2 GUIElement::get_size() const {
    return _size;
}

void GUIElement::set_size(const Vector2 &new_size) {
    _size = new_size;
}

Color GUIElement::get_modulate() const {
    return _modulate;
}

void GUIElement::set_modulate(const Color &new_modulate) {
    _modulate = new_modulate;
}