#pragma once

#include "scene/game_object.h"
#include "math/vector2u.h"

#include <stdint.h>
#include <string>

class GameWindow {
public:
    GameWindow(const Vector2U &resolution, const std::string &title, GameObject *initial_root);
    void load_root(GameObject *new_root, bool unallocate_previous = true);
    void run();
private:
    Vector2U _resolution;
    std::string _title;
    GameObject *_root;
    void _process(sf::RenderWindow *window, GameObject *start, const float &delta);
    void _clean_up();
};