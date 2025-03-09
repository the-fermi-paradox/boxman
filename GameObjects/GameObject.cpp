#include "GameObject.h"

SDL_Rect GameObject::getSprite() const { return this->sprite; }
int GameObject::getX() const { return collider.x; }
int GameObject::getY() const { return collider.y; }
int GameObject::getTop() const { return collider.y; }
int GameObject::getBottom() const { return collider.y + collider.h; }
int GameObject::getLeft() const { return collider.x; }
int GameObject::getRight() const { return collider.x + collider.w; }
GameObject::GameObject(const SDL_Rect sprite, const int x, const int y) :
    sprite(sprite), collider({x, y, sprite.w, sprite.h})
{
}
bool GameObject::samePosition(const GameObject &o) const
{
    return o.getX() == this->getX() && o.getY() == this->getY();
}
