#ifndef BOXMAN_LEVEL_H
#define BOXMAN_LEVEL_H
#include "GameObjects/Player.h"
#include "State.h"

class Level {
public:
    Level(const std::filesystem::path &path, const SpriteSheet &ss);
    explicit Level(const char *path, const SpriteSheet &ss);
    bool checkWin();
    void drawLevel(SpriteSheet &ss) const;
    void reset();
    Player &getPlayer();
    State state;
    bool win = false;

private:
    State start_state;
    Player player;
    int player_start_x;
    int player_start_y;
    int width;
    int height;
};

#endif // BOXMAN_LEVEL_H
