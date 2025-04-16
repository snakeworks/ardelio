#pragma once

#include "math/vector2i.h"
#include "scene/gui/gui_element.h"

#include <vector>

class GUI {
public:
    GUI();
    void on_mouse_moved(Vector2I position);
    void add_gui_element(GUIElement *element);
    void remove_gui_element(GUIElement *element);
private:
    std::vector<GUIElement*> _gui_elements;
};