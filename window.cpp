#include "window.h"

Window::Window(int width, int height) : width(width), height(height) {
    window = SDL_CreateWindow("Boxman",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr)
        ErrorOut("Failed to create window");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

Window::~Window() {
    if (window) SDL_DestroyWindow(window);
}

void Window::Present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer *Window::GetRenderer() {
    return renderer;
}
