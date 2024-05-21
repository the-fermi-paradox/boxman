#ifndef BOXMAN_LEVEL_H
#define BOXMAN_LEVEL_H
#include <nlohmann/json.hpp>
#include <fstream>
#include <spritesheet.h>
#include <gameobject.h>
#include "state.h"
using json = nlohmann::json;

class Level {
public:
    explicit Level(const char *path, SpriteSheet &ss);
    void drawLevel(SpriteSheet &ss);
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

#endif //BOXMAN_LEVEL_H
