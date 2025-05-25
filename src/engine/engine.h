#pragma once

#include "scene/game_object.h"

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

class Engine {
public:
    using instance_creator = std::function<GameObject*()>;
    static void register_type(const std::string &type_name, instance_creator creator);
    static void register_engine_types();

    static GameObject *create(const std::string &type_name);
    static std::vector<std::string> get_all_type_names();

    static void serialize_scene(GameObject *root, const std::string &file_path);
    static GameObject *deserialize_scene(const std::string &file_path);
private:
    static std::unordered_map<std::string, instance_creator> _creators;
};

#define REGISTER_TYPE(TYPE) const bool registered_##TYPE = [] { Engine::register_type(#TYPE, [] { return new TYPE("NewGameObject"); }); return true; }();