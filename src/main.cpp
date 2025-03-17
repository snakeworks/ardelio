#include "../include/Ardelio.h"

int main()
{
    /*Input::addAction({
        "move_right",
        Keycode::D
    });
    Input::addAction({
        "move_left",
        Keycode::A
    });
    Input::addAction({
        "move_up",
        Keycode::W
    });
    Input::addAction({
        "move_down",
        Keycode::S
    });*/

    GameWindow window({1280u, 720u}, "Ardelio");
    
    auto root = GameObject("Root");
    window.root = &root;
    
    auto player = Player2D("Player", window.root);
    player.speed = 160;

    Texture texture("assets/test.png");
    auto sprite = Sprite2D("Sprite", &texture, &player);

    window.run();
}