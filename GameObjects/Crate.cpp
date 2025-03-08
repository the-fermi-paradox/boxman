#include "Crate.h"
#include "State.h"
bool Crate::checkCollision(State &state) const
{
    for (auto &target: state.targets) {
        if (this->samePosition(target)) {
            target.setFilled(true);
        }
    }
    return Moveable::checkCollision(state);
}
