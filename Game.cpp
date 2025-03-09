#include "Game.h"
#include <__algorithm/ranges_all_of.h>
#include <__algorithm/ranges_any_of.h>
#include <filesystem>

#include "Errors.h"

constexpr int TILE_HEIGHT = 64;
constexpr int TILE_WIDTH = 64;
Game::Game(State &&state, SpriteSheet &sprite_sheet) :
    state(state), sprite_sheet(sprite_sheet)
{
    // Check if the path exists and is a directory
    if (const std::filesystem::path levels_path("levels");
        is_directory(levels_path)) {
        for (const auto &entry:
             std::filesystem::directory_iterator(levels_path)) {
            if (entry.is_regular_file()) {
                levels.emplace_back(entry.path(), sprite_sheet);
            }
        }
    } else {
        ErrorOut("levels directory does not exist");
    }
}
bool Game::getGameOver() const { return current_level >= levels.size(); }
void Game::advanceState()
{
    state.player.move(state);
    state.player.nextFrame();
    state.player.setAnimation(sprite_sheet);
    if (this->checkBeatLevel()) {
        this->nextLevel();
    }
}
void Game::nextLevel()
{
    current_level++;
    if (this->getGameOver())
        return;
    this->reset();
}
void Game::reset()
{
    const auto level = this->getCurrentLevel();
    state = level.getState();
}
bool Game::checkBeatLevel()
{
    state.won =
            std::ranges::all_of(state.targets, [&](const auto &target) -> bool {
                return target.getFilled();
            });
    return state.won;
}
