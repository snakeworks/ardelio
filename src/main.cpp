#include <ardelio.h>
#include <SFML/Graphics.hpp>

int main() {
    GameObject root("Root");
    
    Texture white_texture("assets/white32x32.png");
    
    Player2D player("Player");
    player.speed = 250;
    player.set_global_position({1280/2, 720/2});
    
    Sprite2D player_sprite("PlayerSprite", white_texture);
    player_sprite.set_modulate(Color(0, 200, 100, 255));
    player.add_child(&player_sprite);
    
    root.add_child(&player);
    
    GameWindow window({1280u, 720u}, "Test", &root);
    
    PhysicsBody2D rigid_body("RigidBody", CollisionShape(Vector2(32.0f, 32.0f)));
    rigid_body.set_static(false);
    Sprite2D rigid_sprite("RigidSprite", white_texture);
    rigid_sprite.set_size({32u, 32u});
    rigid_body.add_child(&rigid_sprite);
    rigid_body.set_global_position_2d({600, 100});
    root.add_child(&rigid_body);
    window.get_physics_space_2d()->add_body(&rigid_body);

    PhysicsBody2D rigid_body2("RigidBody2", CollisionShape(Vector2(32.0f, 32.0f)));
    rigid_body2.set_static(false);
    Sprite2D rigid_sprite2("RigidSprite2", white_texture);
    rigid_sprite2.set_size({32u, 32u});
    rigid_body2.add_child(&rigid_sprite2);
    rigid_body2.set_global_position_2d({628, 60});
    root.add_child(&rigid_body2);
    window.get_physics_space_2d()->add_body(&rigid_body2);
    
    PhysicsBody2D static_body("StaticBody", CollisionShape(Vector2(500.0f, 32.0f)));
    static_body.set_static(true);
    static_body.set_global_position_2d({600, 600});
    Sprite2D static_sprite("StaticSprite", white_texture);
    static_sprite.set_size({static_cast<uint32_t>(static_body.get_shape().get_size().x), static_cast<uint32_t>(static_body.get_shape().get_size().y)});
    static_body.add_child(&static_sprite);
    root.add_child(&static_body);
    window.get_physics_space_2d()->add_body(&static_body);

    window.run();
}
