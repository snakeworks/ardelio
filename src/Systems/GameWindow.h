#pragma once

#include "../GameObjects/GameObject.h"
#include "../Math/Vector2I.h"

class GameWindow
{
public:
    GameWindow(const Vector2I &resolution, const char *title);
    std::shared_ptr<GameObject> root;
    
    void run();
private:
    Vector2I m_resolution;
    const char *m_title;
};