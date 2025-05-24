#pragma once

#include "scene/game_object.h"

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

class Engine {
public:
    using instance_creator = std::function<GameObject*()>;
    static void register_type(const std::string &type_name, instance_creator creator);
    
    static GameObject *create(const std::string &type_name);
private:
    static std::unordered_map<std::string, instance_creator> _creators;
};

#define REGISTER_TYPE(TYPE) namespace { const bool registered_##TYPE = [] { Engine::register_type(#TYPE, [] { return new TYPE("NewGameObject"); }); return true; }(); }