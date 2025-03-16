#include "Moveable.h"
#include <algorithm>
#include "State.h"
void Moveable::move(State &state)
{
    collider.x += vx;
    if (collider.x < 0 || collider.x >= level_width ||
        this->checkCollision(state)) {
        collider.x -= vx;
    }
    collider.y += vy;
    if (collider.y < 0 || collider.y >= level_height ||
        this->checkCollision(state)) {
        collider.y -= vy;
    }
}
void Moveable::setSpeed(const int x, const int y)
{
    vx = x;
    vy = y;
}
void Moveable::setPosition(const int x, const int y)
{
    collider.x = x;
    collider.y = y;
}
bool Moveable::checkCollision(const GameObject &B) const
{
    auto &A = *this;
    if (&A == &B) {
        return false;
    }
    if (A.getBottom() <= B.getTop()) {
        return false;
    }

    /* The -30 here is to handle the isometric perspective
     * and make things feel more natural. */
    if (A.getTop() >= B.getBottom() - 30) {
        return false;
    }

    if (A.getRight() <= B.getLeft()) {
        return false;
    }

    if (A.getLeft() >= B.getRight()) {
        return false;
    }
    return true;
}

bool Moveable::checkCollision(State &state)
{
    return std::ranges::any_of(state.statics, [&](const auto &el) {
        return this->checkCollision(el);
    });
}
