#ifndef CRATE_H
#define CRATE_H
#include "GameObjects/Moveable.h"

class State;
class Crate : public Moveable {
public:
    using Moveable::Moveable;
    bool checkCollision(State &state) const override;

protected:
};

#endif // CRATE_H
