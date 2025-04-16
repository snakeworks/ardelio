#pragma once

#include "gui_element.h"

class Button : public GUIElement {
public:
    Button(const std::string &name);

    bool has_focus();
    void grab_focus();
    virtual void on_pressed();
    virtual void on_focus();
    virtual void on_focus_lost();
};