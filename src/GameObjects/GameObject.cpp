#include "GameObject.h"
#include <iostream>

GameObject::GameObject(char *name, GameObject *parent)
    : name(name), m_parent(parent)
{
    if (parent)
    {
        parent->addChild(this);
    }
}

GameObject::~GameObject()
{
    for (GameObject* child : m_children)
    {
        delete child;
    }
}

Vector3 GameObject::getGlobalPosition() const
{
    return GameObject::m_globalPosition;
}

void GameObject::setGlobalPosition(const Vector3 &position)
{
    m_globalPosition = position;
    std::cout << position.x << ", " << position.y << std::endl; 
    if (m_parent)
    {
        m_localPosition = m_globalPosition - m_parent->m_globalPosition;
    }
    else
    {
        m_localPosition = m_globalPosition;
    }
    for (GameObject *child : m_children)
    {
        child->setGlobalPosition(child->getLocalPosition() + m_globalPosition);
    }
}

Vector3 GameObject::getLocalPosition() const
{
    return GameObject::m_localPosition;
}

void GameObject::setLocalPosition(const Vector3 &position)
{
    m_localPosition = position;
    if (m_parent)
    {
        m_globalPosition = m_parent->m_globalPosition + m_localPosition;
    } 
    else 
    {
        m_globalPosition = m_localPosition;
    }
    for (GameObject* child : m_children)
    {
        child->setGlobalPosition(child->m_localPosition + m_globalPosition);
    }
}

void GameObject::setParent(GameObject *parent)
{
    GameObject::m_parent = parent;
}

GameObject* GameObject::getParent()
{
    return GameObject::m_parent;
}

void GameObject::addChild(GameObject* child)
{
    m_children.push_back(child);
    child->setParent(this);
}

std::vector<GameObject*> GameObject::getChildren()
{
    return m_children;
}