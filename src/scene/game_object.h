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
    GameObject *find(const std::string &name);

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

    float get_global_rotation() const;
    void set_global_rotation(float new_rotation);
    float get_local_rotation() const;
    void set_local_rotation(float new_rotation);

    std::vector<Property> get_property_list();

    bool has_property(const std::string &name);
    Variant get_property(const std::string &name);
    void set_property(const std::string &name, Variant value);
    virtual std::string nameof_type() const;
protected:
    std::vector<Property> _property_list;
private:
    std::string _name;
    GameWindow *_window;
    Vector3 _local_position;
    float _local_rotation;
    GameObject *_parent;
    std::vector<GameObject*> _children;
    bool _is_freed;
};
