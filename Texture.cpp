#include "Texture.h"
#include <SDL2_image/SDL_image.h>
#include <filesystem>
#include "Errors.h"

Texture::Texture() : renderer(nullptr) {}
Texture::Texture(SDL_Renderer *renderer, std::filesystem::path path) :
    renderer(renderer), path(absolute(path))
{
    this->Refresh();
}

Texture::~Texture()
{
    if (texture)
        SDL_DestroyTexture(texture);
    texture = nullptr;
}

void Texture::Render(const SDL_Rect *sourceRect, const SDL_Rect *destRect) const
{
    if (SDL_RenderCopy(renderer, texture, sourceRect, destRect) < 0) {
        ErrorOut("Failed to copy texture to back buffer");
    }
}
void Texture::Refresh()
{
    if (texture)
        SDL_DestroyTexture(texture);
    texture = IMG_LoadTexture(renderer, path.c_str());
    if (texture == nullptr)
        ErrorOut("Failed to load texture");
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height)) {
        ErrorWithoutExit("Failed to query texture");
        width = 0;
        height = 0;
    }
}

int Texture::GetWidth() const { return width; }

int Texture::GetHeight() const { return height; }
