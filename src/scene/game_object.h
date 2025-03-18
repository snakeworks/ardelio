#pragma once

#include "math/vector3.h"

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

class GameObject {
public:
    GameObject(const std::string &name);
    ~GameObject();
    
    virtual void render();
    virtual void update(const float &delta);
    
    std::string get_name() const;
    void set_name(const std::string &name);
        
    GameObject *get_child(uint32_t index) const;
    const std::vector<GameObject*> &get_children() const;
    void add_child(GameObject *child);
    GameObject *remove_child(GameObject *child);

    GameObject *get_parent() const;
    void reparent(GameObject *new_parent);
    
private:
    std::string _name;
    GameObject *_parent;
    std::vector<GameObject*> _children;
};