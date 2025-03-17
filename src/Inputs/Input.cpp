#include "Input.h"

namespace Input
{
    std::unordered_map<Keycode, bool> map = {};

    void onInputGet(sf::Keyboard::Key sfKeycode, bool isPressed)
    {
        int sfKeycodeIndex = (int)sfKeycode;
        Keycode keycode = static_cast<Keycode>(sfKeycodeIndex);
        map[keycode] = isPressed;
    }

    void addAction(InputAction action)
    {
        //m_inputActions[action.name] = action;
    }
};