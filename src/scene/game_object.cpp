#include "game_object.h"
#include "setup/game_window.h"

#include <algorithm>

GameObject::GameObject(const std::string &name)
    : _name(name), _local_position(Vector3::zero), _rotation(0.0f), _parent(nullptr), _children({}) {}

void GameObject::free() {
    if (get_parent() != nullptr) {
        get_parent()->remove_child(this);
    }
    for (GameObject *child : _children) {
        if (child != nullptr) {
            child->free();
        }
    }
    delete this;
    _children.clear();
}

void GameObject::render(sf::RenderTarget *target) {}
void GameObject::update(float delta) {}
void GameObject::physics_update(float delta) {}

std::string GameObject::get_name() const {
    return _name;
}

void GameObject::set_name(const std::string &name) {
    _name = name;
}

GameWindow *GameObject::get_window() const {
    return _window;
}

void GameObject::set_window(GameWindow *window) {
    _window = window;
    for (GameObject *child : _children) {
        child->set_window(_window);
    }
}

GameObject *GameObject::get_child(uint32_t index) const {
    if (index >= _children.size()) {
        return nullptr;
    }
    return _children[index];
}

const std::vector<GameObject*> &GameObject::get_children() const {
    return _children;
}

void GameObject::add_child(GameObject *child) {
    if (child && child->_parent == nullptr) {
        child->_parent = this;
        child->set_window(_window);
        _children.push_back(child);
    }
}

GameObject *GameObject::remove_child(GameObject *child) {
    auto it = std::find(_children.begin(), _children.end(), child);
    if (it != _children.end()) {
        _children.erase(it);
        child->set_window(nullptr);
        child->_parent = nullptr;
        return child;
    }
    return nullptr;
}

GameObject *GameObject::get_parent() const {
    return _parent;
}

void GameObject::reparent(GameObject *new_parent, bool keep_global_position) {
    if (_parent) {
        _parent->remove_child(this);
    }
    if (new_parent) {
        new_parent->add_child(this);
        if (!keep_global_position) {
            this->set_global_position(new_parent->get_global_position());
        }
    }
}

Vector3 GameObject::get_local_position() const {
    return _local_position;
}

Vector2 GameObject::get_local_position_2d() const {
    return { _local_position.x, _local_position.y };
}

void GameObject::set_local_position(const Vector3 &new_position) {
    _local_position = new_position;
    for (GameObject *child : _children) {
        if (child) {
            child->set_global_position(get_global_position() + child->get_local_position());
        }
    }
}

void GameObject::set_local_position_2d(const Vector2 &new_positon) {
    set_local_position({new_positon.x, new_positon.y, get_local_position().z});
}

Vector3 GameObject::get_global_position() const {
    if (_parent) {
        return _parent->get_global_position() + _local_position;
    }
    return _local_position;
}

Vector2 GameObject::get_global_position_2d() const {
    auto global_pos = get_global_position();
    return { global_pos.x, global_pos.y };
}

void GameObject::set_global_position(const Vector3 &new_position) {
    if (_parent) {
        _local_position = new_position - _parent->get_global_position();
    } else {
        _local_position = new_position;
    }
    for (GameObject *child : _children) {
        if (child) {
            child->set_global_position(new_position + child->get_local_position());
        }
    }
}

void GameObject::set_global_position_2d(const Vector2 &new_position) {
    set_global_position({new_position.x, new_position.y, get_global_position().z});
}

float GameObject::get_rotation() const {
    return _rotation;
}

void GameObject::set_rotation(float new_rotation) {
    _rotation = new_rotation;
    for (GameObject *child : _children) {
        if (child) {
            child->set_rotation(new_rotation);
        }
    }
}

std::vector<Property> GameObject::get_property_list() {
    std::string group_name = "game_object";
    return {
        Property("local_position", group_name, VariantType::VECTOR3, [this]() { 
            Vector3 local_position = this->get_local_position();
            return Variant(VariantType::VECTOR3, &local_position);
        }, [this](Variant variant) { this->set_local_position(variant.as_vector3()); }),
        
        Property("rotation", group_name, VariantType::FLOAT,
            [this]() {
                float rotation = this->get_rotation();
                return Variant(VariantType::FLOAT, &rotation); 
            },
            [this](Variant variant) { this->set_rotation(variant.as_float()); })
    };
}
