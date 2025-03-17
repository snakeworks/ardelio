#include "Player2D.h"
#include "../Inputs/Input.h"
#include <iostream>

Player2D::Player2D(char *name, GameObject *parent)
    : GameObject(name, parent)
{

}

void Player2D::update(float deltaTime)
{
    if (Input::map[Keycode::A])
    {
        setGlobalPosition(getGlobalPosition() - Vector3(1, 0, 0) * deltaTime * speed);
    }
    if (Input::map[Keycode::D])
    {
        setGlobalPosition(getGlobalPosition() + Vector3(1, 0, 0) * deltaTime * speed);
    }
    if (Input::map[Keycode::W])
    {
        setGlobalPosition(getGlobalPosition() - Vector3(0, 1, 0) * deltaTime * speed);
    }
    if (Input::map[Keycode::S])
    {
        setGlobalPosition(getGlobalPosition() + Vector3(0, 1, 0) * deltaTime * speed);
    }
}