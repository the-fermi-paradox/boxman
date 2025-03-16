#include "Crate.h"
#include "State.h"
bool Crate::checkCollision(State &state)
{
    for (auto &target: state.targets) {
        if (this->samePosition(target)) {
            target.setFilled(true);
            locked = true;
            break;
        }
    }
    for (auto &object: state.dynamics) {
        if (this != &object && this->checkCollision(object)) {
            return true;
        }
    }
    return Moveable::checkCollision(state);
}
int Crate::getCollisionMargin() const
{
    printf("I was called!\n");
    return collision_margin;
}
