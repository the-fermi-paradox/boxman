#include "Spritesheet.h"
#include <Errors.h>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
void SpriteSheet::RenderSprite(const int x, const int y,
                               const SDL_Rect &source) const
{
    const SDL_Rect dest = {x, y, source.w, source.h};
    sheet_texture.Render(&source, &dest);
}
void SpriteSheet::RenderSprite(const int x, const int y,
                               const std::string &name) const
{
    if constexpr (ERROR_LOGGING) {
        if (!sprites.contains(name)) {
            ErrorOut("Sprite name not present in map");
        }
    }
    RenderSprite(x, y, sprites.at(name));
}

SpriteSheet::SpriteSheet(SDL_Renderer *renderer,
                         const std::filesystem::path &img_path,
                         const std::filesystem::path &json_path) :
    sheet_texture(Texture(renderer, img_path))
{
    std::ifstream f(absolute(json_path));
    for (json data = json::parse(f)["SubTexture"]; const auto &element: data) {
        std::string name = element["name"];
        sprites[name] = SDL_Rect{element["x"], element["y"], element["width"],
                                 element["height"]};
    }
}
void SpriteSheet::Refresh() { sheet_texture.Refresh(); }
int SpriteSheet::GetSpriteHeight(const std::string &name) const
{
    return sprites.at(name).h;
}
int SpriteSheet::GetSpriteWidth(const std::string &name) const
{
    return sprites.at(name).w;
}
SDL_Rect SpriteSheet::GetSpriteFromName(const std::string &name) const
{
    return sprites.at(name);
}
