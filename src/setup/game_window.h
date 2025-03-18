#pragma once

#include "math/vector2u.h"

#include <stdint.h>
#include <string>

class GameWindow {
public:
    GameWindow(const Vector2U &resolution, const std::string &title);
    void run();
private:
    Vector2U _resolution;
    std::string _title;
};