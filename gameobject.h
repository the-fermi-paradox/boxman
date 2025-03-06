#ifndef BOXMAN_GAMEOBJECT_H
#define BOXMAN_GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "state.h"
constexpr std::string_view ANIM_LEFT[3] = {"player_15", "player_14",
                                           "player_16"};
constexpr std::string_view ANIM_RIGHT[3] = {"player_12", "player_11",
                                            "player_13"};
constexpr std::string_view ANIM_UP[3] = {"player_03", "player_02", "player_04"};
constexpr std::string_view ANIM_DOWN[3] = {"player_01", "player_23",
                                           "player_24"};


class GameObject {
public:
    int level_width = 1000;
    int level_height = 1000;
    bool collidable = true;
    static constexpr int speed = 2;
    GameObject() = default;
    GameObject(std::string type, const int x, const int y, const int w,
               const int h, const bool isPlayer = false,
               const bool collidable = true) :
        collidable(collidable), vx(0), vy(0), type(std::move(type)),
        isPlayer(isPlayer), collider({x, y, w, h})
    {
    }
    void handleEvent(SDL_Event &e);
    void move(State &state);
    void setPosition(int x, int y);
    void setAnimation(int i);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getTop() const;
    [[nodiscard]] int getBottom() const;
    [[nodiscard]] int getLeft() const;
    [[nodiscard]] int getRight() const;
    [[nodiscard]] int getCategory() const;
    [[nodiscard]] std::string getType() const;
    void setSpeed(int x = 0, int y = 0);
    static std::string getType(int n);

private:
    int vx{};
    int vy{};
    std::string type;
    bool isPlayer{};
    SDL_Rect collider{};

    bool checkCollision(const GameObject &B) const;
    bool checkCollision(State &state) const;
};


#endif // BOXMAN_GAMEOBJECT_H
