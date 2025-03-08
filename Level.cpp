#include "Level.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "errors.h"
#include "GameObjects/Crate.h"
#include "GameObjects/Player.h"
constexpr int TILE_HEIGHT = 64;
constexpr int TILE_WIDTH = 64;

using json = nlohmann::json;
Player &Level::getPlayer() { return player; }
Level::Level(const std::filesystem::path &path, const SpriteSheet &ss)
{
    std::ifstream f(path);
    json data = json::parse(f);
    json level_data = data["map"];
    width = static_cast<int>(level_data[0].size());
    height = static_cast<int>(level_data.size());

    player_start_x = data["player_start"]["x"];
    player_start_y = data["player_start"]["y"];
    if (player_start_x < 0 || player_start_x >= width) {
        ErrorOut("Level's starting x coordinate out of bounds.");
    }
    if (player_start_y < 0 || player_start_y >= height) {
        ErrorOut("Level's starting y coordinate out of bounds.");
    }

    for (int i = 0; i < level_data.size(); ++i) {
        for (int j = 0; j < level_data[i].size(); ++j) {
            std::string type = level_data[i][j]["type"];
            std::string sprite = level_data[i][j]["sprite"];
            auto floor =
                    GameObject("floor", "ground_01", j * TILE_WIDTH,
                               i * TILE_HEIGHT, ss.GetSpriteWidth("ground_01"),
                               ss.GetSpriteHeight("ground_01"));
            state.floors.push_back(floor);
            auto addEntity = [&]<typename T>(auto &container) -> void {
                container.push_back(T(
                        type, sprite, j * TILE_WIDTH, i * TILE_HEIGHT,
                        ss.GetSpriteWidth(sprite), ss.GetSpriteHeight(sprite)));
            };
            if (type == "block") {
                addEntity.operator()<Obstacle>(state.statics);
            } else if (type == "target") {
                addEntity.operator()<Target>(state.targets);
            } else if (type == "crate") {
                addEntity.operator()<Crate>(state.dynamics);
            }
        }
    }
    player =
            Player("player", "player_01", player_start_x * TILE_WIDTH,
                   player_start_y * TILE_HEIGHT, ss.GetSpriteWidth("player_01"),
                   ss.GetSpriteHeight("player_01"));
    // Handles resets
    start_state = state;
}
Level::Level(const char *path, const SpriteSheet &ss) :
    Level(std::filesystem::absolute(path), ss)
{
}

void Level::reset()
{
    state = start_state;
    win = false;
    player.setPosition(player_start_x * TILE_WIDTH,
                       player_start_y * TILE_HEIGHT);
}

void Level::drawLevel(SpriteSheet &ss) const
{
    auto render = [&ss](auto &object) -> void {
        ss.RenderSprite(object.getX(), object.getY(), object.getSprite());
    };
    auto renderContainer = [render](auto &container) -> void {
        for (const auto &object: container) {
            render(object);
        }
    };
    renderContainer(state.floors);
    renderContainer(state.targets);
    renderContainer(state.statics);
    renderContainer(state.dynamics);
    render(player);
}
bool Level::checkWin()
{
    for (const auto &target: state.targets) {
        if (!target.getFilled())
            return false;
    }
    return win = true;
}
