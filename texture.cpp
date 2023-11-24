#include "texture.h"

Texture::Texture() : texture(nullptr), renderer(nullptr), width(0), height(0) {}
Texture::Texture(SDL_Renderer *renderer, const char *path) : renderer(renderer) {
    texture = IMG_LoadTexture(renderer, path);
    if (texture == nullptr)
        ErrorOut("Failed to load texture");
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height)) {
        ErrorWithoutExit("Failed to query texture");
        width = 0;
        height = 0;
    }
}

Texture::~Texture() {
    if (texture) SDL_DestroyTexture(texture);
}

void Texture::Render(int x, int y) {
    SDL_Rect r = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &r);
}

int Texture::GetWidth() {
    return width;
}

int Texture::GetHeight() {
    return height;
}
