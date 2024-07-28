#include "window.h"

Window::Window(int width, int height, int lWidth, int lHeight)
: width(width), height(height), lWidth(lWidth), lHeight(lHeight) {
    window = SDL_CreateWindow("Boxman",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
        ErrorOut("Failed to create window");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(renderer, lWidth, lHeight);
    //SDL_RenderSetIntegerScale(renderer, SDL_bool::SDL_TRUE);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

int Window::getLHeight() const {
    return lHeight;
}

int Window::getLWidth() const {
   return lWidth;
}

Window::~Window() {
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
}

void Window::present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer *Window::GetRenderer() {
    return renderer;
}
void Window::clear(){
  SDL_RenderClear(renderer);
}
