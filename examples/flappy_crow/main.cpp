#include "ardelio.h"
#include <vector>

enum GameState {
    MENU,
    PLAYING,
    DEAD
};

struct Pipe {
    GameObject *obj;
    PhysicsBody2D *top;
    PhysicsBody2D *bottom;
    int index = 0;
    bool scored = false;
};

GameState game_state = GameState::MENU;

Text *center_text;
Text *center_text_shadow;
Text *score_text;
Text *score_text_shadow;

PhysicsBody2D *player;
PhysicsBody2D *ground;

std::vector<Pipe> pipes;

uint32_t current_score = 0;

void set_center_text(std::string str) {
    center_text->set_text(str);
    center_text_shadow->set_text(str);
}

void set_score_text(std::string str) {
    score_text->set_text(str);
    score_text_shadow->set_text(str);
}

void restart_game() {
    game_state = GameState::MENU;
    current_score = 0;
    set_score_text(std::to_string(current_score));
    int amount = 1;
    for (auto &pipe : pipes) {
        pipe.scored = false;
        pipe.obj->set_global_position({static_cast<float>(600 * amount), static_cast<float>(rand() % 266), 0});
        amount++;
    }
    player->set_global_position({player->get_global_position().x, 100, 0});
}

void _on_game_start(GameWindow *window) {
    player = dynamic_cast<PhysicsBody2D*>(window->get_root()->find("Player"));
    ground = dynamic_cast<PhysicsBody2D*>(window->get_root()->find("Ground"));
    score_text = dynamic_cast<Text*>(window->get_root()->find("ScoreText"));
    score_text_shadow = dynamic_cast<Text*>(score_text->get_child(0));
    center_text = dynamic_cast<Text*>(window->get_root()->find("CenterText"));
    center_text_shadow = dynamic_cast<Text*>(center_text->get_child(0));

    // Initialize pipes
    for (int i = 1; i <= 2; ++i) { // Adjust the range for more pipes
        GameObject *pipe_obj = window->get_root()->find("Pipe" + std::to_string(i));
        PhysicsBody2D *pipe_top = dynamic_cast<PhysicsBody2D*>(pipe_obj->find("Top"));
        PhysicsBody2D *pipe_bottom = dynamic_cast<PhysicsBody2D*>(pipe_obj->find("Bottom"));
        pipes.push_back({pipe_obj, pipe_top, pipe_bottom, i});
    }
    
    restart_game();
}

void _on_game_end(GameWindow *window) {
    // Handle game end logic if needed
}

bool has_died() {
    for (const auto &pipe : pipes) {
        if (player->get_last_colliding_body() == pipe.top ||
            player->get_last_colliding_body() == pipe.bottom) {
            return true;
        }
    }
    return player->get_last_colliding_body() == ground || player->get_global_position().y < 0;
}

void reset_pipe_position(Pipe &pipe) {
    pipe.scored = false;
    pipe.obj->set_global_position({static_cast<float>(600 * 2), static_cast<float>(rand() % 266), 0});
}

void _update(float delta, GameWindow *window) {
    switch (game_state) {
        case GameState::MENU: {
            player->set_static(true);
            set_center_text("Press 'Space' to Start");
            if (Input::was_pressed_this_frame(Keycode::Space)) {
                game_state = GameState::PLAYING;
                set_center_text("");
            }
            break;
        }
        case GameState::PLAYING: {
            player->set_static(false);

            if (has_died()) {
                game_state = GameState::DEAD;
                return;
            }

            // Player movement
            if (Input::was_pressed_this_frame(Keycode::Space)) {
                Vector2 new_velocity = Vector2(0, player->get_velocity().y);
                new_velocity.y = -300.0f;
                player->set_velocity(new_velocity);
                player->set_global_rotation(0); // Reset rotation when jumping
            }

            // Rotate player based on velocity
            float rotation_angle = std::clamp(player->get_velocity().y * 0.1f, -30.0f, 90.0f) * (3.14159f / 180.0f);
            player->set_global_rotation(rotation_angle);

            // Move pipes
            Vector3 move_factor(-200, 0, 0);
            for (auto &pipe : pipes) {
                Vector3 move_pipe = pipe.obj->get_global_position() + move_factor * delta;
                pipe.obj->set_global_position(move_pipe);

                if (pipe.obj->get_global_position().x <= 0) {
                    reset_pipe_position(pipe);
                }

                if (!pipe.scored && player->get_global_position().x > pipe.obj->get_global_position().x) {
                    pipe.scored = true;
                    current_score++;
                }
            }

            set_score_text(std::to_string(current_score));
            break;
        }
        case GameState::DEAD: {
            set_center_text("You've lost! Press 'R' to Restart.");
            if (Input::was_pressed_this_frame(Keycode::R)) {
                restart_game();
            }
            break;
        }
    }
}

int main() {
    GameWindow window(
        {600u, 720u},
        "Flappy Crow",
        nullptr
    );
    
    GameObject *root = Engine::deserialize_scene("main.ascn");
    
    window.set_on_game_start(_on_game_start);
    window.set_on_game_end(_on_game_end);
    window.set_update(_update);

    window.load_root(root);
    window.run();

    return 0;
}
