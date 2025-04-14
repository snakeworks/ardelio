#include "player_2d.h"
#include "input/input.h"

Player2D::Player2D(const std::string &name)
    : GameObject(name), speed(160) {}

void Player2D::update(float delta) {
    Vector3 dir = Input::as_vector(
        Keycode::A, Keycode::D, Keycode::W, Keycode::S
    );
    dir.normalize();
    set_global_position(get_global_position() + dir * delta * speed);
}