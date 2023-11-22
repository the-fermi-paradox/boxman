#include <SDL.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
            "Boxman",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1080,
            480,
            SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window failed to initialize. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    auto screen_surface = SDL_GetWindowSurface(window);
    if (screen_surface == NULL) {
        printf("Surface failed to initialize. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    if (SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00)) < 0) {
        printf("Failed to fill rectangle. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    if (SDL_UpdateWindowSurface(window) < 0) {
        printf("Failed to update window surface. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
    }
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
}
