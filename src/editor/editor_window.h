#pragma once

#include "ardelio.h"

class EditorWindow {
public:
    EditorWindow();
    ~EditorWindow();
    
    void run();
private:
    GameObject *_root;
    GameObject *_selected_game_object;
    
    void _draw_editor();
    void _draw_game_object(sf::RenderTarget *target, GameObject *current);

    void _add_game_object(const std::string &type_name, GameObject *parent);
    
    void _start_new_scene();
};