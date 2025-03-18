#include "game_window.h"

#include <SFML/Graphics.hpp>

GameWindow::GameWindow(const Vector2U &resolution, const std::string &title)
    : _resolution(resolution), _title(title) {}

void GameWindow::run() {
    sf::RenderWindow window(sf::VideoMode({_resolution.x, _resolution.y}), _title);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }
}