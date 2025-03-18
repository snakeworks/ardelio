#include <ardelio.h>

int main() {
    GameObject root("Root");

    Texture white_texture("assets/white32x32.png");
    Sprite2D square("Square", white_texture);
    
    square.set_modulate(Color(0, 200, 100, 255));

    root.add_child(&square);

    GameWindow window({1280u, 720u}, "Test", &root);

    window.run();
}