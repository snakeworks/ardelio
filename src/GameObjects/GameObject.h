#pragma once

#include "../Math/Vector3.h"
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    char *name;
    virtual void render(sf::RenderWindow *window){}
    virtual void init(){}
    virtual void update(float deltaTime){}
    virtual void input(){}

    Vector3 *getGlobalPosition() const;
    void setGlobalPosition(const Vector3 &value);
    Vector3 *getLocalPosition() const;
    void setLocalPosition(const Vector3 &value);

    GameObject *getParent();
    void setParent(GameObject *parent);

    std::vector<std::shared_ptr<GameObject>> getChildren();
    void addChild(std::shared_ptr<GameObject> child);
    
private:
    Vector3 *m_globalPosition;
    Vector3 *m_localPosition;
    GameObject *m_parent;
    std::vector<std::shared_ptr<GameObject>> m_children;
};