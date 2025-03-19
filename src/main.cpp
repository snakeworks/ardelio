#include <ardelio.h>

int main() {
    GameObject root("Root");

    Texture white_texture("assets/white32x32.png");
    Player2D player("Player");
    player.set_global_position({1280/2, 720/2});
    
    Sprite2D square("Square", white_texture);
    player.add_child(&square);
    
    square.set_modulate(Color(0, 200, 100, 255));

    root.add_child(&player);

    GameWindow window({1280u, 720u}, "Test", &root);

    window.run();
}