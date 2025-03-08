#include "GameObject.h"

std::string GameObject::getSprite() const { return this->sprite; }
int GameObject::getX() const { return collider.x; }
int GameObject::getY() const { return collider.y; }
int GameObject::getTop() const { return collider.y; }
int GameObject::getBottom() const { return collider.y + collider.h; }
int GameObject::getLeft() const { return collider.x; }
int GameObject::getRight() const { return collider.x + collider.w; }
GameObject::GameObject(std::string type, std::string sprite, const int x,
                       const int y, const int w, const int h) :
    type(std::move(type)), sprite(std::move(sprite)), collider({x, y, w, h})
{
}
bool GameObject::samePosition(GameObject &o) const
{
    return (o.getX() == this->getX() && o.getY() == this->getY());
}
