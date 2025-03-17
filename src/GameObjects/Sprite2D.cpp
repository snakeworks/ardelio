#include "Sprite2D.h"
#include <SFML/Graphics.hpp>
#include "../Resources/Texture.h"
#include <iostream>

Sprite2D::Sprite2D(const Texture *texture) : m_sfSprite(texture->sfTexture) {}

void Sprite2D::render(sf::RenderWindow *window)
{
    window->draw(m_sfSprite);
}