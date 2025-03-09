#include "Level.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "GameObjects/Crate.h"
#include "GameObjects/Player.h"
#include "errors.h"
constexpr int TILE_HEIGHT = 64;
constexpr int TILE_WIDTH = 64;

using json = nlohmann::json;
Level::Level(const std::filesystem::path &path, const SpriteSheet &sprite_sheet)
{
    std::ifstream f(path);
    json data = json::parse(f);
    json level_data = data["map"];
    int width = static_cast<int>(level_data[0].size() * TILE_WIDTH);
    int height = static_cast<int>(level_data.size() * TILE_HEIGHT);

    state.player =
            Player(sprite_sheet.GetSpriteFromName("player_01"),
                   static_cast<int>(data["player_start"]["x"]) * TILE_WIDTH,
                   static_cast<int>(data["player_start"]["y"]) * TILE_HEIGHT);
    if (state.player.getX() < 0 || state.player.getX() >= width) {
        ErrorOut("Level's starting x coordinate out of bounds.");
    }
    if (state.player.getY() < 0 || state.player.getY() >= height) {
        ErrorOut("Level's starting y coordinate out of bounds.");
    }

    for (int i = 0; i < level_data.size(); ++i) {
        for (int j = 0; j < level_data[i].size(); ++j) {
            std::string type = level_data[i][j]["type"];
            std::string sprite = level_data[i][j]["sprite"];
            auto floor = GameObject(sprite_sheet.GetSpriteFromName(sprite),
                                    j * TILE_WIDTH, i * TILE_HEIGHT);
            state.floors.push_back(floor);
            auto addEntity = [&]<typename T>(auto &container) -> void {
                container.push_back(T(sprite_sheet.GetSpriteFromName(sprite),
                                      j * TILE_WIDTH, i * TILE_HEIGHT));
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
}
Level::Level(const char *path, const SpriteSheet &ss) :
    Level(std::filesystem::absolute(path), ss)
{
}

State Level::getState() const { return state; }
