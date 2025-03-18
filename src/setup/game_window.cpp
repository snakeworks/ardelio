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
    sf::RenderWindow window(sf::VideoMode({_resolution.x, _resolution.y}), _title);
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color(25, 25, 25));
        _process(&window, _root);
        
        // TODO: Fix segfault when window.display() is called
        window.display();
    }
}

void GameWindow::_process(sf::RenderWindow *window, GameObject *start) {
    if (start == nullptr) {
        return;
    }
    start->render(window);
    for (const auto &child : start->get_children()) {
        _process(window, child);
    }
}