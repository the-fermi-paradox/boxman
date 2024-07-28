#ifndef BOXMAN_TEXTURE_H
#define BOXMAN_TEXTURE_H
#include <SDL2/SDL.h>
#include "errors.h"
#include <SDL2_image/SDL_image.h>
class Texture {
public:
    Texture();
    Texture(SDL_Renderer *renderer, const char *path);
    ~Texture();
    void Render(int x, int y, SDL_Rect *rect= nullptr);
    int GetWidth() const;
    int GetHeight() const;
private:
    int width;
    int height;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
};
#endif //BOXMAN_TEXTURE_H
