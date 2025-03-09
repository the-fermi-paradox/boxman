#ifndef CRATE_H
#define CRATE_H
#include "GameObjects/Moveable.h"

class State;
class Crate : public Moveable {
public:
    using Moveable::Moveable, Moveable::checkCollision;
    bool checkCollision(State &state) override;
    bool locked{};
};

#endif // CRATE_H
