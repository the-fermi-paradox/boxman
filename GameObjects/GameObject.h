#ifndef BOXMAN_GAMEOBJECT_H
#define BOXMAN_GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class GameObject {
public:
    GameObject() = default;
    GameObject(std::string type, std::string sprite, int x, int y,
               int w, int h);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getTop() const;
    [[nodiscard]] int getBottom() const;
    [[nodiscard]] int getLeft() const;
    [[nodiscard]] int getRight() const;
    [[nodiscard]] std::string getSprite() const;
    int level_width = 1000;
    int level_height = 1000;
    static constexpr int speed = 2;

protected:
    std::string type;
    std::string sprite;
    SDL_Rect collider{};
};

#endif // BOXMAN_GAMEOBJECT_H
