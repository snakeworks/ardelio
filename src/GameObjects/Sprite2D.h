#pragma once

#include "GameObject.h"
#include "../Resources/Texture.h"

class Sprite2D : public GameObject
{
public:
    Sprite2D(const Texture *texture);
    void render(sf::RenderWindow *window) override;
    Texture *texture;
private:
    sf::Sprite m_sfSprite;
};