#include "engine.h"
#include "ardelio.h"

std::unordered_map<std::string, Engine::instance_creator> Engine::_creators = {};

void Engine::register_type(const std::string &type_name, instance_creator creator) {
    _creators[type_name] = creator;
}

void Engine::register_engine_types() {
    REGISTER_TYPE(GameObject);
    REGISTER_TYPE(Sprite2D);
}

GameObject *Engine::create(const std::string &type_name) {
    auto it = _creators.find(type_name);
    if (it != _creators.end()) {
        return (it->second)();
    }
    return nullptr;
}

std::vector<std::string> Engine::get_all_type_names() {
    std::vector<std::string> type_names = {};
    for (auto element : _creators) {
        type_names.push_back(element.first);
    }
    return type_names;
}

void Engine::serialize_scene(GameObject *root, const std::string &file_path) {
    
}

GameObject *Engine::deserialize_scene(const std::string &file_path) {
    return nullptr;
}