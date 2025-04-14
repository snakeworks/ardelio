#include "input.h"

std::unordered_map<Keycode, bool> Input::_map = {};

Keycode Input::_from_sf_key(sf::Keyboard::Key sf_key) {
    int key_index = static_cast<int>(sf_key);
    return static_cast<Keycode>(key_index);
} 

const void Input::sf_on_event(const std::optional<sf::Event> &event) {
    if (event->is<sf::Event::KeyPressed>()) {
        Keycode keycode = _from_sf_key(event->getIf<sf::Event::KeyPressed>()->code);
        _map[keycode] = true;
    } else if (event->is<sf::Event::KeyReleased>()) {
        Keycode keycode = _from_sf_key(event->getIf<sf::Event::KeyReleased>()->code);
        _map[keycode] = false;
    }
}

const bool Input::is_pressed(const Keycode keycode) {
    return _map[keycode];
}

const bool Input::was_pressed_this_frame(const Keycode keycode) {
    static std::unordered_map<Keycode, bool> previous_frame_map = _map;

    bool was_pressed = _map[keycode] && !previous_frame_map[keycode];
    previous_frame_map = _map;

    return was_pressed;
}

const Vector2 Input::as_vector(Keycode left, Keycode right, Keycode up, Keycode down) {
    Vector2 vector = Vector2::zero;

    if (is_pressed(left)) vector = vector + Vector2::left;
    if (is_pressed(right)) vector = vector + Vector2::right;
    if (is_pressed(up)) vector = vector + Vector2::up;
    if (is_pressed(down)) vector = vector + Vector2::down;

    return vector;
}
