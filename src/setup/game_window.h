#pragma once

#include "scene/game_object.h"
#include "math/vector2u.h"
#include "physics_space_2d.h"
#include "gui.h"

#include <stdint.h>
#include <functional>
#include <string>

class GameWindow {
public:
    GameWindow(const Vector2U &resolution, const std::string &title, GameObject *initial_root);
    ~GameWindow();
    
    static GameWindow *get_window_of(GameObject *game_object);
    
    GameObject *get_root() const;
    void load_root(GameObject *new_root, bool unallocate_previous = true);
    void set_custom_update(std::function<void(float, sf::RenderWindow*)> func);
    void run();

    void on_game_object_enter(GameObject *game_object);
    void on_game_object_exit(GameObject *game_object);

    PhysicsSpace2D *get_physics_space_2d();
    
    GUI *get_gui();
private:
    static std::vector<GameWindow*> _windows;

    Vector2U _resolution;
    std::string _title;
    GameObject *_root;
    std::function<void(float, sf::RenderWindow*)> _custom_update;
    PhysicsSpace2D _physics_space_2d;
    GUI _gui;
    void _process(sf::RenderWindow *window, GameObject *start, const float &delta);
    void _clean_up();
};