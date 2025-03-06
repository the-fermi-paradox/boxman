#include "texture.h"

#include <__filesystem/path.h>

Texture::Texture() : width(0), height(0), renderer(nullptr), texture(nullptr) {}
Texture::Texture(SDL_Renderer *renderer, const std::filesystem::path &path) :
    renderer(renderer)
{
    texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == nullptr)
        ErrorOut("Failed to load texture");
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height)) {
        ErrorWithoutExit("Failed to query texture");
        width = 0;
        height = 0;
    }
}

Texture::~Texture()
{
    if (texture)
        SDL_DestroyTexture(texture);
}

void Texture::Render(const int x, const int y, const SDL_Rect *rect) const
{
    SDL_Rect r = {x, y, width, height};
    if (rect) {
        r.w = rect->w;
        r.h = rect->h;
    }
    if (SDL_RenderCopy(renderer, texture, rect, &r) < 0) {
        ErrorOut("Failed to copy texture to back buffer");
    }
}

int Texture::GetWidth() const { return width; }

int Texture::GetHeight() const { return height; }
