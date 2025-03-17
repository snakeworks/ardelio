#include "GameWindow.h"
#include "../Math/Vector2I.h"
#include "../Inputs/Input.h"
#include <SFML/Graphics.hpp>
#include <functional>

GameWindow::GameWindow(const Vector2I &resolution, const char *title) : m_resolution(resolution), m_title(title){}

void GameWindow::run()
{
    sf::Clock deltaClock;
    sf::RenderWindow window(sf::VideoMode({m_resolution.x, m_resolution.y}), m_title);
    float delta = 0.0f;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (event->is<sf::Event::KeyPressed>())
            {
                auto sfKeycode = event->getIf<sf::Event::KeyPressed>()->code;
                Input::onInputGet(sfKeycode, true);
            }
            else if (event->is<sf::Event::KeyReleased>())
            {
                auto sfKeycode = event->getIf<sf::Event::KeyReleased>()->code;
                Input::onInputGet(sfKeycode, false);
            }
        }
        
        if (root != nullptr)
        {
            window.clear();
            std::function<void(GameObject*)> processChildren = [&](GameObject* gameObject) {
                gameObject->render(&window);
                gameObject->update(delta);
                for (auto& child : gameObject->getChildren()) {
                    processChildren(child);
                }
            };
            processChildren(root);
            window.display();
        }
        delta = deltaClock.restart().asSeconds();
        float framerate = 1.0f / delta;
        std::cout << "FPS: " << framerate << std::endl;
    }   
}