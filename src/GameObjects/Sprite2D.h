#pragma once

#include "GameObject.h"
#include "../Resources/Texture.h"

class Sprite2D : public GameObject
{
public:
    Sprite2D(char *name, Texture *texture, GameObject *parent = nullptr);
    void render(sf::RenderWindow *window) override;
    Texture *texture;
private:
    sf::Sprite m_sfSprite;
};