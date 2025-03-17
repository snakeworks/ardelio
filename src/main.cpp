#include "../include/Ardelio.h"

int main()
{
    GameWindow window({1280u, 720u}, "Ardelio");
    
    auto root = std::make_shared<GameObject>();    
    window.root = root;

    const Texture texture("assets/test.png");
    auto sprite = std::make_shared<Sprite2D>(&texture);
    root.get()->addChild(sprite);

    window.run();
}