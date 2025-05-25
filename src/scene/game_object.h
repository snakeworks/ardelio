#pragma once

#include "math/vector2.h"
#include "math/vector3.h"
#include "editor/property.h"

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>
#include <SFML/Graphics.hpp>

class GameWindow; // Forward declaration, I need this window man :(

class GameObject {
public:
    GameObject(const std::string &name);
    void free();
    
    virtual void render(sf::RenderTarget *target);
    virtual void update(float delta);
    virtual void physics_update(float delta);

    GameWindow *get_window() const;
    void set_window(GameWindow *window);
    
    std::string get_name() const;
    void set_name(const std::string &name);

    GameObject *get_child(uint32_t index) const;
    const std::vector<GameObject*> &get_children() const;
    void add_child(GameObject *child);
    GameObject *remove_child(GameObject *child);

    GameObject *get_parent() const;
    void reparent(GameObject *new_parent, bool keep_global_position = true);
    
    Vector3 get_local_position() const;
    Vector2 get_local_position_2d() const;
    void set_local_position(const Vector3 &new_position);
    void set_local_position_2d(const Vector2 &new_position);
    
    Vector3 get_global_position() const;
    Vector2 get_global_position_2d() const;
    void set_global_position(const Vector3 &new_position);
    void set_global_position_2d(const Vector2 &new_position);

    float get_rotation() const;
    void set_rotation(float new_rotation);

    virtual std::vector<Property> get_property_list();

private:
    std::string _name;
    GameWindow *_window;
    Vector3 _local_position;
    float _rotation;
    GameObject *_parent;
    std::vector<GameObject*> _children;
};
