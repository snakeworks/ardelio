#include <ardelio.h>
#include <SFML/Graphics.hpp>

Texture white_texture("assets/white64x64.png");

void create_body(GameWindow *window, Vector2 position, Vector2 size, float mass = 1.0f, bool is_static = false) {
    auto *body = new PhysicsBody2D("Body", CollisionShape(size));
    body->set_mass(mass);
    body->set_static(is_static);
    auto *sprite = new Sprite2D("Sprite", white_texture);
    sprite->set_size({static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y)});
    body->add_child(sprite);
    body->set_global_position_2d(position);
    window->get_root()->add_child(body);
    window->get_physics_space_2d()->add_body(body);
}

int main() {
    GameObject root("Root");
    
    
    Player2D player("Player");
    player.speed = 250;
    player.set_global_position({1280/2, 720/2});
    
    Sprite2D player_sprite("PlayerSprite", white_texture);
    player_sprite.set_modulate(Color(0, 200, 100, 255));
    player.add_child(&player_sprite);
    player_sprite.set_size({32u, 32u});
    
    root.add_child(&player);
    
    GameWindow window({1280u, 720u}, "Test", &root);
    
    // Rigid
    create_body(&window, {580, 100}, {32, 32}, 1.0f, false);

    Vector2 base_position = {1000, 100};
    Vector2 size = {32, 32};
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col <= row; ++col) {
            Vector2 position = {
                base_position.x + col * size.x - row * (size.x / 2),
                base_position.y + row * size.y
            };
            create_body(&window, position, size, 1.0f, false);
        }
    }

    // Static
    create_body(&window, {600, 600}, {500, 32}, 5.0f, true);
    create_body(&window, {350, 350}, {32, 500}, 5.0f, true);
    create_body(&window, {850, 500}, {32, 200}, 5.0f, true);
    create_body(&window, {1034, 400}, {400, 32}, 5.0f, true);

    window.get_physics_space_2d()->add_body(&player);

    window.run();
}
