#include "engine.h"
#include "ardelio.h"

#include <fstream>

std::unordered_map<std::string, Engine::instance_creator> Engine::_creators = {};

const std::string Engine::get_version() {
    return "v0.38";
}

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
    std::ofstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for serialization: " + file_path);
    }

    std::function<void(GameObject*, int)> serialize_object = [&](GameObject *object, int indent) {
        if (!object) return;

        std::string indentation(indent * 2, ' ');
        file << indentation << "- name: " << object->get_name() << "\n";
        file << indentation << "  type: " << object->nameof_type() << "\n";

        for (const auto &property : object->get_property_list()) {
            file << indentation << "  " << property.name << ": " << property.get_function().to_string() << "\n";
        }

        file << indentation << "  children:\n";
        for (auto *child : object->get_children()) {
            serialize_object(child, indent + 1);
        }
    };

    serialize_object(root, 0);
    file.close();
}

GameObject *Engine::deserialize_scene(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for deserialization: " + file_path);
    }

    std::function<GameObject *(std::istream &, int &)> deserialize_object = [&](std::istream &stream, int &current_indent) -> GameObject * {
        std::string line;
        std::getline(stream, line);
        if (line.empty()) return nullptr;

        int indent = 0;
        while (indent < line.size() && line[indent] == ' ') {
            ++indent;
        }
        indent /= 2;

        if (indent < current_indent) {
            if (stream.tellg() >= static_cast<std::streampos>(line.size() + 1)) {
                stream.seekg(-static_cast<std::streamoff>(line.size() + 1), std::ios::cur); // Rewind to the start of the line
            }
            return nullptr;
        }

        current_indent = indent;

        std::string name, type;
        if (line.find("- name: ") != std::string::npos) {
            name = line.substr(line.find(": ") + 2);
        }

        std::getline(stream, line);
        if (line.find("type: ") != std::string::npos) {
            type = line.substr(line.find(": ") + 2);
        }

        GameObject *object = Engine::create(type);
        if (!object) {
            throw std::runtime_error("Unknown type during deserialization: " + type);
        }
        object->set_name(name);
        while (std::getline(stream, line)) {
            if (line.empty() || stream.eof()) {
                break;
            }
            if (line.find("children:") != std::string::npos) {
                break;
            }

            size_t colon_pos = line.find(": ");
            if (colon_pos != std::string::npos) {
                std::string property_name = line.substr(line.find_first_not_of(' '), colon_pos - line.find_first_not_of(' '));
                std::string property_value = line.substr(colon_pos + 2);
                Variant variant = Variant::from_string(property_value);
                object->set_property(property_name, variant);
            }
        }

        while (true) {
            int child_indent = current_indent + 1;
            GameObject *child = deserialize_object(stream, child_indent);
            if (!child) break;
            object->add_child(child);
        }

        return object;
    };

    int current_indent = -1;
    GameObject *root = deserialize_object(file, current_indent);
    file.close();
    return root;
}
