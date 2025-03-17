#include "GameObject.h"

Vector3 *GameObject::getGlobalPosition() const
{
    return GameObject::m_globalPosition;
}

void GameObject::setGlobalPosition(const Vector3 &position)
{
    *GameObject::m_globalPosition = position;
    if (GameObject::m_parent != nullptr)
    {
        *GameObject::m_localPosition = position - *GameObject::m_parent->getGlobalPosition();
    }
    else
    {
        *GameObject::m_localPosition = position;
    }
}

Vector3* GameObject::getLocalPosition() const
{
    return GameObject::m_localPosition;
}

void GameObject::setLocalPosition(const Vector3 &position)
{
    *GameObject::m_localPosition = position;
    if (GameObject::m_parent != nullptr)
    {
        *GameObject::m_globalPosition = position + *GameObject::m_parent->getGlobalPosition();
    }
    else
    {
        *GameObject::m_globalPosition = position;
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

void GameObject::addChild(std::shared_ptr<GameObject> child)
{
    m_children.push_back(child);
    child->setParent(this);
}

std::vector<std::shared_ptr<GameObject>> GameObject::getChildren()
{
    return m_children;
}