#include "editor_window.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

EditorWindow::EditorWindow() {

}

EditorWindow::~EditorWindow() {

}

void EditorWindow::run() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Ardelio");
    window.setFramerateLimit(60);
    bool _ = ImGui::SFML::Init(window, true);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");

        ImGui::Button("Press me!");

        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}