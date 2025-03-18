#include "game_object.h"

#include <algorithm>

GameObject::GameObject(const std::string &name)
    : _name(name), _parent(nullptr), _children({}) {}

GameObject::~GameObject() {
    for (GameObject *child : _children) {
        delete child;
    }
    _children.clear();
}

std::string GameObject::get_name() const {
    return _name;
}

void GameObject::set_name(const std::string &name) {
    _name = name;
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
    if (child) {
        child->_parent = this;
        _children.push_back(child);
    }
}

GameObject *GameObject::remove_child(GameObject *child) {
    auto it = std::find(_children.begin(), _children.end(), child);
    if (it != _children.end()) {
        _children.erase(it);
        child->_parent = nullptr;
        return child;
    }
    return nullptr;
}

GameObject *GameObject::get_parent() const {
    return _parent;
}

void GameObject::reparent(GameObject *new_parent) {
    if (_parent) {
        _parent->remove_child(this);
    }
    if (new_parent) {
        new_parent->add_child(this);
    }
}
