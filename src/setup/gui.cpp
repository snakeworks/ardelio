#include "gui.h"
#include <algorithm>

GUI::GUI() : _gui_elements({}) {}

void GUI::on_mouse_moved(Vector2I position) {

}

void GUI::add_gui_element(GUIElement *element) {
    _gui_elements.push_back(element);
}

void GUI::remove_gui_element(GUIElement *element) {
    auto it = std::find(_gui_elements.begin(), _gui_elements.end(), element);
    if (it != _gui_elements.end()) {
        _gui_elements.erase(it);
    }
}