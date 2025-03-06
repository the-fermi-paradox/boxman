#ifndef BOXMAN_LEVEL_H
#define BOXMAN_LEVEL_H
#include <fstream>
#include <gameobject.h>
#include <nlohmann/json.hpp>
#include <spritesheet.h>
#include "state.h"
using json = nlohmann::json;

class Level {
public:
    Level(const std::filesystem::path &path, const SpriteSheet &ss);
    explicit Level(const char *path, const SpriteSheet &ss);
    void drawLevel(SpriteSheet &ss) const;
    void reset();
    GameObject &getPlayer();
    State state;

private:
    State start_state;
    GameObject player;
    int player_start_x;
    int player_start_y;
    int width;
    int height;
};

#endif // BOXMAN_LEVEL_H
