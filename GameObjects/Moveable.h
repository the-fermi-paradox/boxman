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
    int collision_margin{30};
    int vx{};
    int vy{};
    [[nodiscard]] virtual bool checkCollision(const GameObject &B) const;
    virtual bool checkCollision(State &state);
    [[nodiscard]] virtual int getCollisionMargin() const;
};

#endif // MOVEABLE_H
