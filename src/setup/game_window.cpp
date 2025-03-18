#include "game_window.h"

#include <iostream>
#include <SFML/Graphics.hpp>

GameWindow::GameWindow(const Vector2U &resolution, const std::string &title, GameObject *initial_root)
    : _resolution(resolution), _title(title), _root(initial_root) {}

void GameWindow::load_root(GameObject *new_root, bool unallocate_previous) {
    if (unallocate_previous) {
        delete _root;
    }
    if (new_root == nullptr) {
        return;
    }
    _root = new_root;
}

void GameWindow::run() {
    sf::Clock clock = sf::Clock();
    sf::RenderWindow window(sf::VideoMode({_resolution.x, _resolution.y}), _title);
    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color(15, 15, 15));
        _process(&window, _root, delta);
        
        // TODO: Fix segfault when window.display() is called
        window.display();
    }
}

void GameWindow::_process(sf::RenderWindow *window, GameObject *current, const float &delta) {
    if (current == nullptr) {
        return;
    }
    current->render(window);
    current->update(delta);
    for (const auto &child : current->get_children()) {
        _process(window, child, delta);
    }
}