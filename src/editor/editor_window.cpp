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
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        if (obj == _selected_game_object) {
            flags |= ImGuiTreeNodeFlags_Selected;
        }
        if (obj->get_children().empty()) {
            flags |= ImGuiTreeNodeFlags_Leaf;
        }
        if (ImGui::TreeNodeEx(obj->get_name().c_str(), flags)) {
            if (ImGui::IsItemClicked()) {
                _selected_game_object = obj;
            }
            for (const auto& child : obj->get_children()) {
                draw_tree_node(child);
            }
            ImGui::TreePop();
        } else if (ImGui::IsItemClicked()) {
            _selected_game_object = obj;
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
    ImGui::Text("Selected Object: %s", _selected_game_object == nullptr ? "None" : _selected_game_object->get_name().c_str());
    if (_selected_game_object != nullptr) {
        for (const auto &property : _selected_game_object->get_property_list()) {
            ImGui::Text("%s", property.name.c_str());
            switch (property.variant_type) {
                case VariantType::FLOAT: {
                    float rotation = property.get_function().as_float();
                    if (ImGui::DragFloat("##", &rotation, 0.01f, 0.0f, 6.28f)) {
                        property.set_function(Variant(VariantType::FLOAT, &rotation));
                    }
                    break;
                }
                case VariantType::VECTOR3: {
                    auto cur_value = property.get_function().as_vector3();
                    float positions[3] = {cur_value.x, cur_value.y, cur_value.z};
                    if (ImGui::DragFloat3("##", positions)) {
                        Vector3 new_pos(positions[0], positions[1], positions[2]);
                        property.set_function(Variant(VariantType::VECTOR3, &new_pos));
                    }
                    break;
                }
            }
        }
    }
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