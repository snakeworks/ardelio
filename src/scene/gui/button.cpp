#include "button.h"
#include "engine/engine.h"

Button::Button(const std::string &name) : GUIElement(name) {}

std::string Button::nameof_type() const {
    return NAMEOF(Button);
}