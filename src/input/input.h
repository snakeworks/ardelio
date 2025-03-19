#pragma once

#include "keycode.h"
#include "math/vector3.h"

#include <unordered_map>
#include <SFML/Graphics.hpp>

class Input {
public:
    static const void sf_on_event(const std::optional<sf::Event> &event);
    static const bool is_pressed(const Keycode keycode);
    static const Vector3 as_vector(Keycode left, Keycode right, Keycode up, Keycode down);

private:
    static std::unordered_map<Keycode, bool> _map;
    static Keycode _from_sf_key(sf::Keyboard::Key sf_key);
};