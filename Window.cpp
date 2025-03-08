#include "Window.h"

Window::Window(const int width, const int height, const int lWidth,
               const int lHeight) :
    lWidth(lWidth), lHeight(lHeight), width(width), height(height)
{
    window = SDL_CreateWindow("Boxman", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE |
                                      SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == nullptr)
        ErrorOut("Failed to create window");
    renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(renderer, lWidth, lHeight);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

int Window::getLHeight() const { return lHeight; }
int Window::getWidth() const
{
    int x = 0;
    int y = 0;
    if (SDL_GetRendererOutputSize(renderer, &x, &y) < 0) {
       ErrorOut("Failed to get renderer output size");
    }
    return x;
}
int Window::getHeight() const
{
    int x = 0;
    int y = 0;
    if (SDL_GetRendererOutputSize(renderer, &x, &y) < 0) {
       ErrorOut("Failed to get renderer output size");
    }
    return y;
}

int Window::getLWidth() const { return lWidth; }

Window::~Window()
{
    if (window)
        SDL_DestroyWindow(window);
    if (renderer)
        SDL_DestroyRenderer(renderer);
}

void Window::present() const { SDL_RenderPresent(renderer); }

SDL_Renderer *Window::GetRenderer() const { return renderer; }
void Window::clear() const { SDL_RenderClear(renderer); }
