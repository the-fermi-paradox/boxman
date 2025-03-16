#ifndef CRATE_H
#define CRATE_H
#include "GameObjects/Moveable.h"

class State;
class Crate : public Moveable {
public:
    using Moveable::Moveable, Moveable::checkCollision;
    bool checkCollision(State &state) override;
    bool locked{};

protected:
    int collision_margin{0};
    [[nodiscard]] int getCollisionMargin() const override;
};

#endif // CRATE_H
