#ifndef BOXMAN_SPRITESHEET_H
#define BOXMAN_SPRITESHEET_H

#include <unordered_map>
#include <SDL2/SDL.h>
#include "Texture.h"

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
