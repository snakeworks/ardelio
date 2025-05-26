#pragma once

#include "ardelio.h"

enum EditorWindowPopupType {
    NONE,
    OBJECT_PICKER,
    OBJECT_RENAME
};

class EditorWindow {
public:
    EditorWindow();
    ~EditorWindow();
    
    void run();
private:
    GameObject *_root;
    GameObject *_selected_game_object;

    EditorWindowPopupType _current_popup;
    
    void _draw_editor();
    void _draw_game_object(sf::RenderTarget *target, GameObject *current);
    void _draw_object_picker_popup();

    void _add_game_object(const std::string &type_name, GameObject *parent);
    
    void _start_new_scene();
    void _load_scene_from_path(const std::string &file_path);

    void _run_debug_mode();
};