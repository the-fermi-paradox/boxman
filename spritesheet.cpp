#include "spritesheet.h"

void SpriteSheet::RenderSprite(const int x, const int y,
                               const std::string &name)
{
    if constexpr (ERROR_LOGGING) {
        if (!sprites.contains(name)) {
            ErrorOut("Sprite name not present in map");
        }
    }
    sheet_texture.Render(x, y, &sprites[name]);
}

SpriteSheet::SpriteSheet(SDL_Renderer *renderer,
                         const std::filesystem::path &img_path,
                         const std::filesystem::path &json_path) :
    sheet_texture(Texture(renderer, img_path))
{
    std::ifstream f(json_path);
    for (json data = json::parse(f)["SubTexture"]; const auto &element: data) {
        std::string name = element["name"];
        sprites[name] = SDL_Rect{element["x"], element["y"], element["width"],
                                 element["height"]};
    }
}
SpriteSheet::SpriteSheet(SDL_Renderer *renderer, const char *img_path,
                         const char *json_path) :
    SpriteSheet(renderer, std::filesystem::absolute(img_path),
                std::filesystem::absolute(json_path))
{
}
int SpriteSheet::GetSpriteHeight(const std::string &name) const
{
    return sprites.at(name).h;
}
int SpriteSheet::GetSpriteWidth(const std::string &name) const
{
    return sprites.at(name).w;
}
