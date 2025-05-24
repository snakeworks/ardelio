#include "editor_window.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>

sf::RenderWindow _window;

EditorWindow::EditorWindow() {

}

EditorWindow::~EditorWindow() {
    
}

void EditorWindow::run() {
    _window = sf::RenderWindow(sf::VideoMode({1280, 720}), "Ardelio");
    _window.setFramerateLimit(60);
    bool _ = ImGui::SFML::Init(_window, true);
    
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    _start_new_scene();
    
    sf::Clock deltaClock;
    while (_window.isOpen()) {
        while (const auto event = _window.pollEvent()) {
            ImGui::SFML::ProcessEvent(_window, *event);
            
            if (event->is<sf::Event::Closed>()) {
                _window.close();
            }
        }
        
        ImGui::SFML::Update(_window, deltaClock.restart());
        
        _draw_editor();

        // Drawing the viewport outside the _draw_editor function
        // because drawing it inside the function completely breaks it.
        // I have never in my life seen a problem like this. Why? Just why?
        // How is it even possible to have such a problem? Is it C++?
        // Is it ImGui? Is it SFML? Who knows! All I know is that this is
        // terrible but it works.
        ImGui::Begin("Viewport");
        static ImVec2 viewportSize{500, 500};
        sf::RenderTexture viewportTexture({static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y)});
        viewportTexture.clear(sf::Color::Black);
        viewportSize = ImGui::GetContentRegionAvail();
        ImGui::Image(viewportTexture);
        ImGui::End();
        _draw_game_object(&viewportTexture, _root);

        _window.clear();
        ImGui::SFML::Render(_window);
        _window.display();
    }
    
    ImGui::SFML::Shutdown();
}

void EditorWindow::_draw_editor() {    
    // Fullscreen dockspace
    ImGui::DockSpaceOverViewport();
    
    // Drawing main menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("New Scene");
            ImGui::MenuItem("Open");
            ImGui::MenuItem("Save");
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) {
                _window.close();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::MenuItem("Undo");
            ImGui::MenuItem("Redo");
            ImGui::Separator();
            ImGui::MenuItem("Preferences");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Project")) {
            ImGui::MenuItem("Project Settings");
            ImGui::MenuItem("Build");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Drawing scene tree
    ImGui::Begin("Scene Tree");
    std::function<void(GameObject*)> draw_tree_node = [&](GameObject* obj) {
        ImGuiTreeNodeFlags flags = obj->get_children().empty() ? ImGuiTreeNodeFlags_Leaf : 0;
        if (ImGui::TreeNodeEx(obj->get_name().c_str(), flags)) {
            for (const auto& child : obj->get_children()) {
                draw_tree_node(child);
            }
            ImGui::TreePop();
        }
    };
    
    if (_root != nullptr) {
        draw_tree_node(_root);
    }
    ImGui::End();
    
    // Drawing file system
    ImGui::Begin("File System");
    std::function<void(const char*, const std::vector<std::string>&)> draw_folder = [&](const char* folder_name, const std::vector<std::string>& files) {
        if (ImGui::TreeNodeEx((std::string("[] ") + folder_name).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            for (const auto &file : files) {
                ImGui::Text("%s", file.c_str());
            }
            ImGui::TreePop();
        }
    };

    draw_folder("data", {"player.png", "background.png", "main.ascn"});
    ImGui::End();
    
    // Drawing inspector
    ImGui::Begin("Inspector");
    ImGui::Text("Selected Object: Player");
    ImGui::Separator();
    ImGui::Text("Transform");
    ImGui::InputFloat3("Position", new float[3]{0, 0, 0});
    ImGui::InputFloat3("Rotation", new float[3]{0, 0, 0});
    ImGui::InputFloat3("Scale", new float[3]{1, 1, 1});
    ImGui::Separator();
    ImGui::Text("Sprite Renderer");
    ImGui::InputText("Texture", (char*)"Player.png", 64);
    ImGui::End();
}

void EditorWindow::_draw_game_object(sf::RenderTarget *target, GameObject *current) {
    if (current == nullptr) {
        return;
    }

    current->render(target);

    for (const auto &child : current->get_children()) {
        _draw_game_object(target, child);
    }
}

void EditorWindow::_start_new_scene() {
    if (_root != nullptr) {
        _root->free();
    }
    auto texture = new Texture("assets/white64x64.png");
    _root = new GameObject("root");
    auto sprite = new Sprite2D("MySprite", *texture);
    _root->add_child(sprite);
    _root->set_global_position({640, 480});
}