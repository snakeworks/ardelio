#pragma once

#include "math/vector3.h"

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>
#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject(const std::string &name);
    void free();
    
    virtual void render(sf::RenderWindow *window);
    virtual void update(float delta);
    
    std::string get_name() const;
    void set_name(const std::string &name);

    GameObject *get_child(uint32_t index) const;
    const std::vector<GameObject*> &get_children() const;
    void add_child(GameObject *child);
    GameObject *remove_child(GameObject *child);

    GameObject *get_parent() const;
    void reparent(GameObject *new_parent, bool keep_global_position = true);
    
    Vector3 get_local_position() const;
    void set_local_position(const Vector3 &new_position);
    Vector3 get_global_position() const;
    void set_global_position(const Vector3 &new_position);

private:
    std::string _name;
    Vector3 _local_position;
    GameObject *_parent;
    std::vector<GameObject*> _children;
};