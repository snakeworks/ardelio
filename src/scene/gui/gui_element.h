#pragma once

#include "scene/game_object.h"
#include "math/color.h"

class GUIElement : public GameObject {
public:
    GUIElement(const std::string &name);

    Color get_modulate() const;
    void set_modulate(const Color &new_modulate);
private:
    Color _modulate;
};