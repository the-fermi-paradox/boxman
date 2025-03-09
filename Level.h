#ifndef BOXMAN_LEVEL_H
#define BOXMAN_LEVEL_H
#include "GameObjects/Player.h"
#include "State.h"

class Level {
public:
    Level(const std::filesystem::path &path, const SpriteSheet &sprite_sheet);
    explicit Level(const char *path, const SpriteSheet &ss);
    [[nodiscard]] State getState() const;

private:
    State state;
};

#endif // BOXMAN_LEVEL_H
