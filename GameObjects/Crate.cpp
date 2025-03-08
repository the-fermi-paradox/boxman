#include "Crate.h"
#include "State.h"
bool Crate::checkCollision(State &state) const
{
    for (auto &target: state.targets) {
        if (this->samePosition(target)) {
            target.setFilled(true);
        }
    }
    for (auto &object: state.dynamics) {
        if (this != &object && this->checkCollision(object)) {
            return true;
        }
    }
    return Moveable::checkCollision(state);
}
