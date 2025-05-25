#pragma once

#include "scene/game_object.h"
#include "math/color.h"

class GUIElement : public GameObject {
public:
    GUIElement(const std::string &name);

    Vector2 get_size() const;
    void set_size(const Vector2 &new_size);

    Color get_modulate() const;
    void set_modulate(const Color &new_modulate);

    virtual std::string nameof_type() const override;
private:
    Vector2 _size;
    Color _modulate;
};