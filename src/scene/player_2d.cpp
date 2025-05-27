#include "player_2d.h"
#include "input/input.h"
#include "engine/engine.h"

Player2D::Player2D(const std::string &name)
    : PhysicsBody2D(name), speed(160) {
    set_mass(8.0f);
}

void Player2D::update(float delta) {
    // Horizontal movement
    Vector2 dir = Input::as_vector(Keycode::A, Keycode::D, Keycode::W, Keycode::S);
    Vector2 horizontal_velocity = Vector2(dir.x * speed, get_velocity().y);

    // Jumping
    if (Input::was_pressed_this_frame(Keycode::Space)) {
        // Check if the player is on the ground
        horizontal_velocity.y = -410.0f; // Jump force
    }

    // Set the new velocity
    set_velocity(horizontal_velocity);
}

std::string Player2D::nameof_type() const {
    return NAMEOF(Player2D);
}
