#ifndef BOXMAN_TEXTURE_H
#define BOXMAN_TEXTURE_H
#include <SDL.h>
#include "errors.h"
#include <SDL2_image/SDL_image.h>
class Texture {
public:
    Texture();
    Texture(SDL_Renderer *renderer, const char *path);
    ~Texture();
    void Render(int x, int y) {
       SDL_Rect r = {x, y, width, height};
       SDL_RenderCopy(renderer, texture, nullptr, &r);
    }
    SDL_Texture *texture;
    SDL_Renderer *renderer;
private:
    int width;
    int height;

};
#endif //BOXMAN_TEXTURE_H
