#include "GameObject.h"

class Player2D : public GameObject
{
public:
    Player2D(char *name, GameObject *parent);
    void update(float deltaTime) override;
    float speed;
};