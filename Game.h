#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Level.h"

class Game {
public:
    Game() = delete;
    Game(State &&state, SpriteSheet &ss);
    [[nodiscard]] bool getGameOver() const;
    void advanceState();
    void nextLevel();
    void gotoLevel(int level);
    void reset();
    bool checkBeatLevel();
    State state;

private:
    auto getCurrentLevel() { return levels[current_level]; }
    int current_level{-1};
    SpriteSheet sprite_sheet;
    std::vector<Level> levels;
};

#endif // GAME_H
