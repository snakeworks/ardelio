#include "GameWindow.h"
#include "../Math/Vector2I.h"
#include <SFML/Graphics.hpp>
#include <functional>

GameWindow::GameWindow(const Vector2I &resolution, const char *title) : m_resolution(resolution), m_title(title){}

void GameWindow::run()
{
    sf::Clock deltaClock;
    float deltaTime = 0.0f;
    
    sf::RenderWindow window(sf::VideoMode({m_resolution.x, m_resolution.y}), m_title);
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (root != nullptr)
        {
            window.clear();
            std::function<void(std::shared_ptr<GameObject>)> renderChildren = [&](std::shared_ptr<GameObject> gameObject) {
                gameObject.get()->render(&window);
                for (auto& child : gameObject.get()->getChildren()) {
                    renderChildren(child);
                }
            };
            renderChildren(root);
            window.display();
        }

        deltaTime = deltaClock.restart().asSeconds();
    }   
}