#include "game_window.h"
#include "input/input.h"

#include <SFML/Graphics.hpp>

std::vector<GameWindow*> GameWindow::_windows = {};

GameWindow::GameWindow(const Vector2U &resolution, const std::string &title, GameObject *initial_root)
    : _resolution(resolution), _title(title), _root(initial_root) {
    _windows.push_back(this);
}

GameWindow::~GameWindow() {
    // TODO: Implement destructor
}

GameWindow *GameWindow::get_window_of(GameObject *game_object) {
    auto potential_root = game_object;
    while (true) {
        if (potential_root->get_parent() == nullptr) {
            break;
        }
        potential_root = potential_root->get_parent();
    }
    for (auto window : _windows) {
        if (window->_root == potential_root) {
            return window;
        }
    }
    return nullptr;
}

GameObject *GameWindow::get_root() const {
    return _root;
}

void GameWindow::load_root(GameObject *new_root, bool unallocate_previous) {
    if (new_root == nullptr) {
        return;
    }
    if (_root != nullptr) {
        on_game_object_exit(_root);
        if (unallocate_previous) {
            _root->free();
        }
    }
    _root = new_root;
    _root->set_window(this);
    on_game_object_enter(_root);
}

void GameWindow::set_custom_update(std::function<void(float, sf::RenderWindow*)> func) {
    GameWindow::_custom_update = func;
}

void GameWindow::run() {
    sf::Clock clock = sf::Clock();
    sf::RenderWindow window(sf::VideoMode({_resolution.x, _resolution.y}), _title);
    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            Input::sf_on_event(event, this);
        }
        
        window.clear(sf::Color(15, 15, 15));
        _process(&window, _root, delta);
        if (_custom_update) {
            _custom_update(delta, &window);
        }
        _physics_space_2d.physics_update(delta);

        // TODO: Fix segfault when window.display() is called
        window.display();
    }
}

void GameWindow::on_game_object_enter(GameObject *game_object) {
    if (auto physics_body = dynamic_cast<PhysicsBody2D*>(game_object)) {
        _physics_space_2d.add_body(physics_body);
    } else if (auto gui_element = dynamic_cast<GUIElement*>(game_object)) {
        _gui.add_gui_element(gui_element);
    }
}

void GameWindow::on_game_object_exit(GameObject *game_object) {
    if (auto physics_body = dynamic_cast<PhysicsBody2D*>(game_object)) {
        _physics_space_2d.remove_body(physics_body);
    } else if (auto gui_element = dynamic_cast<GUIElement*>(game_object)) {
        _gui.remove_gui_element(gui_element);
    }
}

PhysicsSpace2D *GameWindow::get_physics_space_2d() {
    return &_physics_space_2d;
}

GUI *GameWindow::get_gui() {
    return &_gui;
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

void GameWindow::_clean_up() {}