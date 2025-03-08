#ifndef BOXMAN_TEXTURE_H
#define BOXMAN_TEXTURE_H
#include <SDL2/SDL.h>
#include <__filesystem/path.h>
class Texture {
public:
    Texture();
    Texture(SDL_Renderer *renderer, std::filesystem::path path);
    ~Texture();
    void Render(int x, int y, const SDL_Rect *rect = nullptr) const;
    void Refresh();
    int GetWidth() const;
    int GetHeight() const;

private:
    int width{};
    int height{};
    const std::filesystem::path path;
    SDL_Renderer *renderer;
    SDL_Texture *texture{};
};
#endif // BOXMAN_TEXTURE_H
