#include <SFML/Graphics.hpp>
#include "Texture.h"

Texture::Texture(const char *path) : Texture::Resource(path)
{
    Texture::sfTexture = sf::Texture(path);
};