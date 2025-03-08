#ifndef CRATE_H
#define CRATE_H
#include "GameObjects/Moveable.h"

class Crate : public Moveable {
public:
    using Moveable::Moveable;

public:
    [[nodiscard]] bool checkCollision(const GameObject &object) const
    {
        return Moveable::checkCollision(object);
    }

protected:
};

#endif // CRATE_H
