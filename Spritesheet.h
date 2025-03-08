#ifndef BOXMAN_SPRITESHEET_H
#define BOXMAN_SPRITESHEET_H

#include <SDL2/SDL.h>
#include <errors.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Texture.h"
using json = nlohmann::json;

class SpriteSheet {
public:
    SpriteSheet(SDL_Renderer *renderer, const std::filesystem::path &img_path,
                const std::filesystem::path &json_path);
    void Refresh();
    void RenderSprite(int x, int y, const std::string &name);
    [[nodiscard]] int GetSpriteWidth(const std::string &name) const;
    [[nodiscard]] int GetSpriteHeight(const std::string &name) const;

private:
    std::unordered_map<std::string, SDL_Rect> sprites;
    Texture sheet_texture;
};

#endif // BOXMAN_SPRITESHEET_H
