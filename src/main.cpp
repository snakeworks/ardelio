#include <ardelio.h>

int main() {
    GameObject root("Root");

    Texture white_texture("assets/white32x32.png");
    Player2D player("Player");
    player.speed = 250;
    player.set_global_position({1280/2, 720/2});
    
    Sprite2D player_sprite("Sprite", white_texture);
    player_sprite.set_modulate(Color(0, 200, 100, 255));
    player.add_child(&player_sprite);

    Sprite2D red_square("RedSquare", white_texture);
    red_square.set_modulate(Color(200, 10, 0));
    red_square.set_global_position({1000, 500});

    root.add_child(&player);
    root.add_child(&red_square);

    GameWindow window({1280u, 720u}, "Test", &root);

    window.run();
}