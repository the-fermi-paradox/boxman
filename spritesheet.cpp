#include "spritesheet.h"

void SpriteSheet::RenderSprite(int x, int y, const std::string &name) {
    if constexpr (ERROR_LOGGING) {
        if (sprites.find(name) == sprites.end()) {
            ErrorOut("Sprite name not present in map");
        }
    }
    sheet_texture.Render(x, y, &sprites[name]);
}

SpriteSheet::SpriteSheet(SDL_Renderer *renderer, const char *img_path, const char *json_path)
        : sheet_texture(Texture(renderer, img_path)) {
    std::ifstream f(json_path);
    json data = json::parse(f)["SubTexture"];
    for (const auto &element : data) {
        std::string name = element["name"];
        sprites[name] = SDL_Rect{element["x"], element["y"], element["width"], element["height"]};
    }
}
int SpriteSheet::GetSpriteHeight(const std::string& name) {
  return sprites[name].h;
}
int SpriteSheet::GetSpriteWidth(const std::string& name) {
  return sprites[name].w;
}
