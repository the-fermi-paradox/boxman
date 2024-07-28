#include "level.h"
constexpr int TILE_HEIGHT = 64;
constexpr int TILE_WIDTH  = 64;

GameObject& Level::getPlayer() {
  return player;
}
Level::Level(const char *path, SpriteSheet &ss) {
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

    for (size_t i = 0; i < level_data.size(); ++i) {
        for (size_t j = 0; j < level_data[i].size(); ++j) {
            int type = level_data[i][j];
            std::string s = GameObject::getType(type);
            GameObject floor = GameObject("ground_01", j * TILE_WIDTH, i * TILE_HEIGHT,
                                      ss.GetSpriteWidth("ground_01"), ss.GetSpriteHeight("ground_01"));
            GameObject g = GameObject(s, j * TILE_WIDTH, i * TILE_HEIGHT,
                                      ss.GetSpriteWidth(s), ss.GetSpriteHeight(s));
            state.floors.push_back(floor);
            if (g.getCategory() == 1) {
              g.collidable = (s != "environment_01");
              state.statics.push_back(g);
            } else if (g.getCategory() == 2) {
              g.collidable = true;
              state.dynamics.push_back(g);
            }
        }
    }
    player = GameObject("player_01",
                        player_start_x * TILE_WIDTH,
                        player_start_y * TILE_HEIGHT,
                        ss.GetSpriteWidth("player_01"),
                        ss.GetSpriteHeight("player_01"),
                        true);
    /* Copy state into start state for handling resets */
    start_state = state;
}

void Level::reset() {
    state = start_state;
    player.setPosition(player_start_x * TILE_WIDTH, player_start_y * TILE_HEIGHT);
}

void Level::drawLevel(SpriteSheet &ss) {
    /* Render all background stuff here */
    for (const auto& object : state.floors) {
      ss.RenderSprite(object.getX(), object.getY(), object.getType());
    }
    for (const auto& object : state.statics) {
      ss.RenderSprite(object.getX(), object.getY(), object.getType());
    }
    /* Render all stateful objects here */
    for (const auto& object : state.dynamics) {
        ss.RenderSprite(object.getX(), object.getY(), object.getType());
    }
    ss.RenderSprite(player.getX(), player.getY(), player.getType());
}
