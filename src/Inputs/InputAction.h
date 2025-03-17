#pragma once

#include "Keycode.h"

class InputAction
{
public:
    char *name;
    Keycode keycode;
    bool isPressed();
    bool isReleased();
};