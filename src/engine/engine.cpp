#include "engine.h"

std::unordered_map<std::string, Engine::instance_creator> Engine::_creators = {};

void Engine::register_type(const std::string &type_name, instance_creator creator) {
    _creators[type_name] = creator;
}

GameObject *Engine::create(const std::string &type_name) {
    auto it = _creators.find(type_name);
    if (it != _creators.end()) {
        return (it->second)();
    }
    return nullptr;
}