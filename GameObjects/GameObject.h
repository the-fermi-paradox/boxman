#ifndef BOXMAN_GAMEOBJECT_H
#define BOXMAN_GAMEOBJECT_H

#include <SDL2/SDL.h>

class GameObject {
public:
    virtual ~GameObject() = default;
    GameObject() = default;
    GameObject(SDL_Rect sprite, int x, int y);
    bool samePosition(GameObject &o) const;
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getTop() const;
    [[nodiscard]] int getBottom() const;
    [[nodiscard]] int getLeft() const;
    [[nodiscard]] int getRight() const;
    [[nodiscard]] SDL_Rect getSprite() const;
    int level_width = 1000;
    int level_height = 1000;
    static constexpr int speed = 2;

protected:
    SDL_Rect sprite;
    SDL_Rect collider{};
};

#endif // BOXMAN_GAMEOBJECT_H
