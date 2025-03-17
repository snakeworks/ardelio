#pragma once

#include "Keycode.h"
#include "InputAction.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Input
{
    extern std::unordered_map<Keycode, bool> map;

    void onInputGet(sf::Keyboard::Key sfKeycode, bool isPressed);
    void addAction(InputAction action);
};