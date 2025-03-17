#include "Sprite2D.h"
#include <SFML/Graphics.hpp>
#include "../Resources/Texture.h"
#include <iostream>

Sprite2D::Sprite2D(char *name, Texture *texture, GameObject *parent)
    : GameObject(name, parent), texture(texture), m_sfSprite(texture->sfTexture) {}

void Sprite2D::render(sf::RenderWindow *window)
{
    m_sfSprite.setPosition({getGlobalPosition().x, getGlobalPosition().y});
    window->draw(m_sfSprite);
}
