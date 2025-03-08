#ifndef BOXMAN_LEVEL_H
#define BOXMAN_LEVEL_H
#include <Spritesheet.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "GameObjects/GameObject.h"
#include "GameObjects/Obstacle.h"

#include "GameObjects/Player.h"
#include "State.h"
using json = nlohmann::json;

class Level {
public:
    Level(const std::filesystem::path &path, const SpriteSheet &ss);
    explicit Level(const char *path, const SpriteSheet &ss);
    void drawLevel(SpriteSheet &ss) const;
    void reset();
    Player &getPlayer();
    State state;

private:
    State start_state;
    Player player;
    int player_start_x;
    int player_start_y;
    int width;
    int height;
};

#endif // BOXMAN_LEVEL_H
