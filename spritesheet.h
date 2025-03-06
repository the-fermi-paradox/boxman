#ifndef BOXMAN_SPRITESHEET_H
#define BOXMAN_SPRITESHEET_H

#include <SDL2/SDL.h>
#include <errors.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <texture.h>
using json = nlohmann::json;

/* Sprite sheets are instantiated by passing in a Spritesheet alongside a map
 * JSON file */
class SpriteSheet {
public:
    SpriteSheet(SDL_Renderer *renderer, const std::filesystem::path &img_path,
                const std::filesystem::path &json_path);
    SpriteSheet(SDL_Renderer *renderer, const char *img_path,
                const char *json_path);
    void Refresh();
    void RenderSprite(int x, int y, const std::string &name);
    int GetSpriteWidth(const std::string &name) const;
    int GetSpriteHeight(const std::string &name) const;

private:
    std::unordered_map<std::string, SDL_Rect> sprites;
    Texture sheet_texture;
};

#endif // BOXMAN_SPRITESHEET_H
