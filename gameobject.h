#ifndef BOXMAN_GAMEOBJECT_H
#define BOXMAN_GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "state.h"
constexpr std::string_view ANIM_LEFT[3] = {"player_15", "player_14", "player_16"};
constexpr std::string_view ANIM_RIGHT[3] = {"player_12", "player_11", "player_13"};
constexpr std::string_view ANIM_UP[3] = {"player_03", "player_02", "player_04"};
constexpr std::string_view ANIM_DOWN[3] = {"player_01", "player_23", "player_24"};


class GameObject {
public:
    int level_width = 1000;
    int level_height = 1000;
    bool collidable = true;
    static constexpr int speed = 2;
    GameObject() = default;
    GameObject(std::string type, int x, int y, int w, int h, bool isPlayer=false, bool collidable=true)
    : type(std::move(type)), collider({x, y, w, h}), vx(0), vy(0), isPlayer(isPlayer), collidable(collidable) {}
    void handleEvent(SDL_Event &e);
    void move(State &state);
    void setPosition(int x, int y);
    void setAnimation(int i);
    int getX() const;
    int getY() const;
    int getTop() const;
    int getBottom() const;
    int getLeft() const;
    int getRight() const;
    int getCategory() const;
    void setSpeed(int x=0, int y=0);
    std::string getType() const;
    static std::string getType(int n);
private:
    int vx;
    int vy;
    std::string type;
    bool isPlayer;
    SDL_Rect collider;

    bool checkCollision(const GameObject &B);
    bool checkCollision(State &state);
};


#endif //BOXMAN_GAMEOBJECT_H