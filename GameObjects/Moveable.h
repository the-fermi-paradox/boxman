#ifndef MOVEABLE_H
#define MOVEABLE_H
#include "GameObjects/GameObject.h"

class State;
class Moveable : public GameObject {
public:
    using GameObject::GameObject;
    void setPosition(int x, int y);
    void move(State &state);
    void setSpeed(int x, int y);

protected:
    int vx{};
    int vy{};
    [[nodiscard]] bool checkCollision(const GameObject &B) const;
    virtual bool checkCollision(State &state);
};

#endif // MOVEABLE_H
